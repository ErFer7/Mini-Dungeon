#include "components/collider_component.hpp"

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "entities/entity.hpp"
#include "managers/graphics_component_manager.hpp"
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
        Handle<GraphicsComponent> graphics_component = this->get_entity()->get_component<GraphicsComponent>();

        this->_rectangle = graphics_component->get_rectangle();
    }

    this->_update_rectangle();

    Handle<PhysicsComponent> physics_component = this->get_entity()->get_component<PhysicsComponent>();

    if (!physics_component.is_null()) {
        this->_physics_component = physics_component;
        physics_component->set_collider_component(this->make_handle<ColliderComponent>());
    }
}

// TODO: Add support for rotation
void ColliderComponent::_update_rectangle() {
    log_trace(this, __PRETTY_FUNCTION__);

    Vector2Df position = this->_transform_component->get_position();
    Vector2Df scale = this->_transform_component->get_scale();

    this->_rectangle.x = position.x;
    this->_rectangle.y = position.y;
    this->_rectangle.width = this->_rectangle.width * scale.x;
    this->_rectangle.height = this->_rectangle.height * scale.y;
}
