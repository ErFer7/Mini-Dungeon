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

void PhysicsComponent::debug_draw() {
    Vector2Df position = this->_transform_component->get_position();
    position.y *= -1.0f;

    Vector2Df velocity = this->_velocity;
    velocity.y *= -1.0f;

    Vector2Df acceleration = this->_acceleration;
    acceleration.y *= -1.0f;

    DrawLineV(position, position + (velocity * 0.1f), WHITE);
    DrawLineV(position, position + (acceleration * 0.1f), BLUE);
}

void PhysicsComponent::_move(PhysicsComponent &&other) {
    if (this == &other) {
        return;
    }

    this->_velocity = std::move(other._velocity);
    this->_acceleration = std::move(other._acceleration);
    this->_drag = std::move(other._drag);
    this->_time = std::move(other._time);
    this->_is_statically_stable = std::move(other._is_statically_stable);
    this->_is_colliding = std::move(other._is_colliding);
    this->_transform_component = std::move(other._transform_component);
    this->_collider_component = std::move(other._collider_component);
}
