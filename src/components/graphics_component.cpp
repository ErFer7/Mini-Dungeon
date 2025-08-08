#include "../../include/components/graphics_component.hpp"

#include <raylib.h>

#include "../../include/entities/entity.hpp"
#include "../../include/game_core.hpp"

GraphicsComponent::GraphicsComponent(GameCore *game_core, Entity *entity, RenderingMode rendering_mode)
    : Component(game_core, entity, false) {
    this->_texture = Texture2D();
    this->_source_rectangle = {0, 0, 0, 0};
    this->_destination_rectangle = {0, 0, 0, 0};
    this->_origin = {0, 0};
    this->_tint = WHITE;
    this->_rendering_mode = rendering_mode;
    this->_layer = 0;
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();

    this->_transform_update_listener =
        TransformComponent::TransformUpdateListener([this](const Vector2 &, const TransformData &) { this->_update_transform(); });

    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());
}

GraphicsComponent::~GraphicsComponent() { this->unregister_component(); }

// TODO: Use static cast for conversions
void GraphicsComponent::set_texture(const Texture2D texture) {
    this->_texture = texture;
    this->_source_rectangle = {0, 0, (float)this->_texture.width, (float)this->_texture.height};
    this->_origin = {(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f};
    this->_update_transform();
}

Rectangle GraphicsComponent::get_rectangle() const {
    return Rectangle{this->_destination_rectangle.x - this->_destination_rectangle.width / 2.0f,
                     this->_destination_rectangle.y - this->_destination_rectangle.height / 2.0f,
                     this->_destination_rectangle.width,
                     this->_destination_rectangle.height};
}

void GraphicsComponent::draw() {
    DrawTexturePro(this->_texture, this->_source_rectangle, this->_destination_rectangle, this->_origin, this->_rotation, this->_tint);
}

void GraphicsComponent::register_component() { this->get_game_core()->get_graphics_component_manager()->register_component(this); }

void GraphicsComponent::unregister_component() { this->get_game_core()->get_graphics_component_manager()->unregister_component(this); }

void GraphicsComponent::_update_transform() {
    this->_origin = Vector2Multiply(Vector2{(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f},
                                    this->_transform_component->get_scale());
    this->_rotation = this->_transform_component->get_rotation();
    this->_destination_rectangle = {this->_transform_component->get_position().x,
                                    this->_transform_component->get_position().y,
                                    (float)this->_texture.width * this->_transform_component->get_scale().x,
                                    (float)this->_texture.height * this->_transform_component->get_scale().y};
}
