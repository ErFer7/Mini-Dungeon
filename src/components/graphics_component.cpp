#include "../../include/components/graphics_component.hpp"

#include <raylib.h>

#include "../../include/entities/entity.hpp"
#include "../../include/game_core.hpp"
#include "utils/vector.hpp"

GraphicsComponent::GraphicsComponent(GameCore *game_core, Entity *entity, const GraphicsComponentArgs &args)
    : Component(game_core, entity), _rendering_mode(args.rendering_mode), _color(args.color), _layer(args.layer) {
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();

    this->_transform_update_listener.set_callable([this](const Vector2Df &, const TransformData &) { this->_update_drawing_transform(); });
    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());

    this->set_texture(args.texture);
}

GraphicsComponent::~GraphicsComponent() { this->unregister_component(); }

void GraphicsComponent::set_texture(const Texture2D texture) {
    this->_texture = texture;
    this->_source_rectangle = {0, 0, static_cast<float>(this->_texture.width), static_cast<float>(this->_texture.height)};
    this->_update_drawing_transform();
}

Rectangle GraphicsComponent::get_rectangle() const {
    return Rectangle{this->_destination_rectangle.x - this->_destination_rectangle.width / 2.0f,
                     this->_destination_rectangle.y - this->_destination_rectangle.height / 2.0f,
                     this->_destination_rectangle.width,
                     this->_destination_rectangle.height};
}

void GraphicsComponent::draw() {
    DrawTexturePro(this->_texture, this->_source_rectangle, this->_destination_rectangle, this->_origin, this->_rotation, this->_color);
}

void GraphicsComponent::register_component() { this->get_game_core()->get_graphics_component_manager()->register_component(this); }

void GraphicsComponent::unregister_component() { this->get_game_core()->get_graphics_component_manager()->unregister_component(this); }

void GraphicsComponent::_update_drawing_transform() {
    float half_width = static_cast<float>(this->_texture.width) / 2.0f;
    float half_height = static_cast<float>(this->_texture.height) / 2.0f;

    this->_origin = Vector2Df(half_width, half_height) * this->_transform_component->get_scale();
    this->_rotation = this->_transform_component->get_rotation();
    this->_destination_rectangle = {this->_transform_component->get_position().x,
                                    this->_transform_component->get_position().y,
                                    (float)this->_texture.width * this->_transform_component->get_scale().x,
                                    (float)this->_texture.height * this->_transform_component->get_scale().y};
}
