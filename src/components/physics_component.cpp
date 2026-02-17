#include "components/physics_component.hpp"

#include <raylib.h>

#include "components/collider_component.hpp"
#include "components/component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"
#include "utils/vector.hpp"

PhysicsComponent::PhysicsComponent(Handle<Entity> entity, const PhysicsComponentArgs &args)
    : _velocity(args.initial_velocity),
      _acceleration(args.initial_acceleration),
      _drag(args.drag),
      _time(GetTime()),
      _is_statically_stable(!args.initial_velocity.is_zero() || !args.initial_acceleration.is_zero()),
      _is_colliding(false),
      Component(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_transform_component = this->get_entity()->get_component<TransformComponent>();
    this->_collider_component = this->get_entity()->get_component<ColliderComponent>();

    this->_collider_component->set_physics_component(this->make_handle<PhysicsComponent>());
}

void PhysicsComponent::update() {
    double current_time = GetTime();
    this->_time_diff = static_cast<float>(current_time - this->_time);
    this->_time = current_time;

    if (this->_is_statically_stable) {
        return;
    }

    this->_transform_component->translate(this->_velocity * this->_time_diff);

    this->_velocity += this->_acceleration * this->_time_diff;
    this->_acceleration = -this->_velocity * this->_drag;

    bool is_velocity_stable = false;
    bool is_acceleration_stable = false;

    if (this->_velocity.magnitude() < FLOAT_EPSILON) {
        this->_velocity = Vector2Df();
        is_velocity_stable = true;
    }

    if (this->_acceleration.magnitude() < FLOAT_EPSILON) {
        this->_acceleration = Vector2Df();
        is_acceleration_stable = true;
    }

    this->_is_statically_stable = is_velocity_stable && is_acceleration_stable && !this->_is_colliding;
}
