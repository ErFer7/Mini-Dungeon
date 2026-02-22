#include "components/collider_component.hpp"

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "entities/entity.hpp"
#include "managers/graphics_manager.hpp"
#include "raylib.h"

ColliderComponent::ColliderComponent(Handle<Entity> entity, const ColliderComponentArgs &args)
    : _rectangle(args.rectangle),
      Component(entity) {
    // FIX: Args
    log_trace(this, __PRETTY_FUNCTION__);

    this->_transform_component = this->get_entity()->get_component<TransformComponent>();
    this->_transform_update_listener
        .bind_callable<ColliderComponent, &ColliderComponent::_update_rectangle_listener_call>(
            this->make_handle<ColliderComponent>());
    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());

    if (this->_rectangle.width == 0.0f && this->_rectangle.height == 0.0f) {
        log_info(this, "ColliderComponent: Using the graphics rect for the collider");

        Handle<GraphicsComponent> graphics_component = this->get_entity()->get_component<GraphicsComponent>();

        Vector2Df sprite_size = graphics_component->get_size();

        this->_rectangle = Rectangle{0.0f, 0.0f, sprite_size.x, sprite_size.y};
    }

    this->_offset = Vector2Df(this->_rectangle.x, this->_rectangle.y);

    this->_update_rectangle();

    Handle<PhysicsComponent> physics_component = this->get_entity()->get_component<PhysicsComponent>();

    if (!physics_component.is_null()) {
        this->_physics_component = physics_component;
        physics_component->set_collider_component(this->make_handle<ColliderComponent>());
    }
}

void ColliderComponent::debug_draw() {
    DrawRectangleLines(this->_rectangle.x - this->_rectangle.width / 2.0f,
                       -(this->_rectangle.y + this->_rectangle.height / 2.0f),
                       this->_rectangle.width,
                       this->_rectangle.height,
                       RED);
}

// TODO: Add support for rotation
void ColliderComponent::_update_rectangle() {
    log_trace(this, __PRETTY_FUNCTION__);

    Vector2Df position = this->_transform_component->get_position();
    Vector2Df scale = this->_transform_component->get_scale();

    this->_rectangle.x = position.x + this->_offset.x;
    this->_rectangle.y = position.y + this->_offset.y;
    this->_rectangle.width = this->_rectangle.width * scale.x;
    this->_rectangle.height = this->_rectangle.height * scale.y;
}
