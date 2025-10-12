#include "components/physics_component.hpp"

#include <raylib.h>

#include "components/collider_component.hpp"
#include "components/component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"
#include "game_core.hpp"
#include "utils/vector.hpp"

PhysicsComponent::PhysicsComponent(GameCore *game_core, Entity *entity, const PhysicsComponentArgs &args)
    : _velocity(args.initial_velocity),
      _acceleration(args.initial_acceleration),
      _drag(args.drag),
      _time(GetTime()),
      Component(game_core, entity) {
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();
    this->_collider_component = this->get_entity()->get_component<ColliderComponent>();
}

PhysicsComponent::~PhysicsComponent() { this->unregister_component(); }

void PhysicsComponent::update() {
    double current_time = GetTime();
    float time_diff = static_cast<float>(current_time - this->_time);
    this->_time = current_time;

    if (this->_velocity.is_zero() && this->_acceleration.is_zero()) {
        return;
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

void PhysicsComponent::register_component() {
    this->get_game_core()->get_physics_component_manager()->register_component(this);
}

void PhysicsComponent::unregister_component() {
    this->get_game_core()->get_physics_component_manager()->unregister_component(this);
}
