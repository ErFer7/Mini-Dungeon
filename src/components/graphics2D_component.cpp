#include "../../include/components/graphics2D_component.hpp"

#include <raylib.h>

#include "../../include/engine_core.hpp"
#include "../../include/entities/entity.hpp"
#include "utils/transform.hpp"

Graphics2DComponent::Graphics2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, false) {
    this->_texture = Texture2D();
    this->_source_rectangle = {0, 0, 0, 0};
    this->_destination_rectangle = {0, 0, 0, 0};
    this->_origin = {0, 0};
    this->_tint = WHITE;
    this->_rendering_mode = RenderingMode::WORLD_SPACE_2D;
    this->_layer = 0;
    this->_transform_component = this->get_entity()->get_component<Transform2DComponent>();

    this->_transform_update_listener =
        Transform2DComponent::TransformUpdateListener([this](const Vector2 &, const Transform2D &) {
            this->_update_transform();
        });

    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());
}

Graphics2DComponent::~Graphics2DComponent() { this->unregister_component(); }

void Graphics2DComponent::set_texture(const Texture2D texture) {
    this->_texture = texture;
    this->_source_rectangle = {0, 0, (float)this->_texture.width, (float)this->_texture.height};
    this->_origin = {(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f};
    this->_update_transform();
}

void Graphics2DComponent::draw() {
    DrawTexturePro(this->_texture, this->_source_rectangle, this->_destination_rectangle, this->_origin, this->_rotation, this->_tint);
}

void Graphics2DComponent::register_component() { this->get_engine_core()->get_graphics_manager()->register_component(this); }

void Graphics2DComponent::unregister_component() { this->get_engine_core()->get_graphics_manager()->unregister_component(this); }

void Graphics2DComponent::_update_transform() {
    this->_origin = Vector2Multiply(Vector2{(float)this->_texture.width / 2.0f, (float)this->_texture.height / 2.0f},
                                    this->_transform_component->get_scale());
    this->_rotation = this->_transform_component->get_rotation();
    this->_destination_rectangle = {this->_transform_component->get_position().x,
                                    this->_transform_component->get_position().y,
                                    (float)this->_texture.width * this->_transform_component->get_scale().x,
                                    (float)this->_texture.height * this->_transform_component->get_scale().y};
}
