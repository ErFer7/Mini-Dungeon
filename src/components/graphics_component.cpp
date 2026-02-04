#include "components/graphics_component.hpp"

#include <raylib.h>

#include "entities/entity.hpp"
#include "game_core.hpp"
#include "managers/graphics_component_manager.hpp"
#include "utils/vector.hpp"

// TODO: Register this component in the right space
GraphicsComponent::GraphicsComponent(GameCore *game_core, Entity *entity, const GraphicsComponentArgs &args)
    : Component(game_core, entity),
      _rendering_mode(args.rendering_mode),
      _texture_scale(args.texture_scale),
      _color(args.color),
      _layer(args.layer) {
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();

    this->_transform_update_listener.set_callable(
        [this](const Vector2Df &, const TransformData &) { this->_update_drawing_transform(); });
    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());

    this->set_texture(args.texture);

    this->get_game_core()->get_graphics_component_manager()->register_component_on_space(this);

    this->_on_destroy_listener.set_callable([this](Component *) { this->_unregister_on_space(); });
    this->_on_destroy_listener.subscribe(this->get_on_destroy_event());
}

void GraphicsComponent::set_texture(const Texture2D texture) {
    this->_texture = texture;
    this->_source_rectangle.x = 0;
    this->_source_rectangle.y = 0;
    this->_source_rectangle.width = static_cast<float>(this->_texture.width);
    this->_source_rectangle.height = static_cast<float>(this->_texture.height);

    this->_update_drawing_transform();
}

Rectangle GraphicsComponent::get_rectangle() const {
    return Rectangle{this->_destination_rectangle.x - this->_destination_rectangle.width / 2.0f,
                     this->_destination_rectangle.y - this->_destination_rectangle.height / 2.0f,
                     this->_destination_rectangle.width,
                     this->_destination_rectangle.height};
}

void GraphicsComponent::draw() {
    DrawTexturePro(this->_texture,
                   this->_source_rectangle,
                   this->_destination_rectangle,
                   this->_origin,
                   this->_rotation,
                   this->_color);
}

void GraphicsComponent::_update_drawing_transform() {
    float width = static_cast<float>(this->_texture.width);
    float height = static_cast<float>(this->_texture.height);

    float y_axis_orientation = this->_rendering_mode == RenderingMode::WORLD_SPACE_2D ? -1.0f : 1.0f;

    Vector2Df scale = this->_transform_component->get_scale();

    this->_origin = Vector2Df(width / 2.0f, height / 2.0f) * scale;
    this->_rotation = this->_transform_component->get_rotation();

    Vector2Df position = this->_transform_component->get_position();

    this->_destination_rectangle.x = position.x;
    this->_destination_rectangle.y = position.y * y_axis_orientation;
    this->_destination_rectangle.width = width * scale.x * this->_texture_scale;
    this->_destination_rectangle.height = height * scale.y * this->_texture_scale;
}

void GraphicsComponent::_unregister_on_space() {
    this->get_game_core()->get_graphics_component_manager()->unregister_component_on_space(this);
}
