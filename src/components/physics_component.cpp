#include "components/physics_component.hpp"

#include <raylib.h>

#include "components/collider_component.hpp"
#include "components/component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"
#include "utils/vector.hpp"

PhysicsComponent::PhysicsComponent(Entity *entity, const PhysicsComponentArgs &args)
    : _velocity(args.initial_velocity),
      _acceleration(args.initial_acceleration),
      _drag(args.drag),
      _time(GetTime()),
      _is_statically_stable(!args.initial_velocity.is_zero() || !args.initial_acceleration.is_zero()),
      Component(entity) {
    utils::log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_transform_component = this->get_entity()->get_component<TransformComponent>();
    this->_collider_component = this->get_entity()->get_component<ColliderComponent>();
}

void PhysicsComponent::update() {
    double current_time = GetTime();
    float time_diff = static_cast<float>(current_time - this->_time);
    this->_time = current_time;

    if (this->_is_statically_stable) {
        return;
    }

    if (this->_velocity.is_zero() && this->_acceleration.is_zero() && !this->_is_colliding) {
        this->_is_statically_stable = true;
    }

    this->_transform_component->translate(this->_velocity * time_diff);

    this->_velocity += this->_acceleration * time_diff;
    this->_acceleration = -this->_velocity * this->_drag;

    if (this->_velocity.magnitude() < FLOAT_EPSILON) {
        this->_velocity = Vector2Df();
    }

    if (this->_acceleration.magnitude() < FLOAT_EPSILON) {
        this->_acceleration = Vector2Df();
    }
}
