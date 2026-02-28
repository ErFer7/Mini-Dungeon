#include "components/graphics_component.hpp"

#include <raylib.h>

#include "components/transform_component.hpp"
#include "entities/entity.hpp"
#include "game_core.hpp"
#include "managers/graphics/graphics_manager.hpp"
#include "utils/vector.hpp"

// TODO: Register this component in the right space
GraphicsComponent::GraphicsComponent(Handle<Entity> entity, const GraphicsComponentArgs &args)
    : Component(entity),
      _rendering_mode(args.rendering_mode),
      _texture_scale(args.texture_scale),
      _color(args.color),
      _layer(args.layer) {
    log_trace(this, __PRETTY_FUNCTION__, entity);
    Handle<TransformComponent> transform_component = this->get_entity()->get_component<TransformComponent>();

    Handle<GraphicsComponent> handle = this->make_handle<GraphicsComponent>();

    this->_transform_update_listener
        .bind_callable<GraphicsComponent, &GraphicsComponent::_update_drawing_transform_listener_call>(handle);
    this->_transform_update_listener.subscribe(transform_component->get_on_update_event());

    this->set_texture(args.texture);

    GameCore::get_graphics_manager()->register_component_on_space(handle);

    this->_on_destroy_listener.bind_callable<GraphicsComponent, &GraphicsComponent::_unregister_on_space_listener_call>(
        handle);
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

Vector2Df GraphicsComponent::get_size() const {
    return Vector2Df(this->_destination_rectangle.width, this->_destination_rectangle.height);
}

void GraphicsComponent::draw() {
    DrawTexturePro(this->_texture,
                   this->_source_rectangle,
                   this->_destination_rectangle,
                   this->_origin,
                   this->_rotation,
                   this->_color);
}

void GraphicsComponent::_move(GraphicsComponent &&other) {
    if (this == &other) {
        return;
    }

    this->_texture = std::move(other._texture);
    this->_source_rectangle = std::move(other._source_rectangle);
    this->_destination_rectangle = std::move(other._destination_rectangle);
    this->_origin = std::move(other._origin);
    this->_rotation = std::move(other._rotation);
    this->_texture_scale = std::move(other._texture_scale);
    this->_color = std::move(other._color);
    this->_rendering_mode = std::move(other._rendering_mode);
    this->_layer = std::move(other._layer);
    this->_transform_update_listener = std::move(other._transform_update_listener);
    this->_on_destroy_listener = std::move(other._on_destroy_listener);
}

void GraphicsComponent::_update_drawing_transform() {
    float width = static_cast<float>(this->_texture.width);
    float height = static_cast<float>(this->_texture.height);

    float y_axis_orientation = this->_rendering_mode == RenderingMode::WORLD_SPACE_2D ? -1.0f : 1.0f;

    // OPTIMIZE: Use diff transformations from the event and avoid getting the transform from the entity
    Handle<TransformComponent> transform_component = this->get_entity()->get_component<TransformComponent>();

    Vector2Df scale = transform_component->get_scale();

    float scaled_width = width * scale.x * this->_texture_scale;
    float scaled_height = height * scale.y * this->_texture_scale;

    this->_origin = Vector2Df(scaled_width, scaled_height) / 2.0f;
    this->_rotation = transform_component->get_rotation();

    Vector2Df position = transform_component->get_position();

    this->_destination_rectangle.x = position.x;
    this->_destination_rectangle.y = position.y * y_axis_orientation;
    this->_destination_rectangle.width = scaled_width;
    this->_destination_rectangle.height = scaled_height;
}

void GraphicsComponent::_unregister_on_space() {
    GameCore::get_graphics_manager()->unregister_component_on_space(this->make_handle<GraphicsComponent>());
}
