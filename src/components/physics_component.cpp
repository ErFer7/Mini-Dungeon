#include "../../include/components/physics_component.hpp"

#include "../../include/definitions.hpp"
#include "../../include/entities/entity.hpp"
#include "../../include/game_core.hpp"
#include "components/component.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

PhysicsComponent::PhysicsComponent(GameCore *game_core, Entity *entity, const PhysicsComponentArgs &args)
    : _velocity(args.initial_velocity),
      _acceleration(args.initial_acceleration),
      _drag(args.drag),
      _time(GetTime()),
      Component(game_core, entity) {
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();
}

PhysicsComponent::~PhysicsComponent() { this->unregister_component(); }

void PhysicsComponent::update() {
    float time_diff = static_cast<float>(GetTime() - this->_time);

    if (this->_velocity.is_zero() && this->_acceleration.is_zero()) {
        return;
    }

    this->_transform_component->translate(this->_velocity * time_diff);

    this->_velocity += this->_acceleration * time_diff;
    this->_acceleration *= this->_drag * time_diff;

    float epsilon = FLOAT_EPSILON;

    if (this->_velocity.magnitude() < epsilon) {
        this->_velocity = Vector2Df();
    }

    if (this->_acceleration.magnitude() < epsilon) {
        this->_acceleration = Vector2Df();
    }
}

void PhysicsComponent::register_component() { this->get_game_core()->get_physics_component_manager()->register_component(this); }

void PhysicsComponent::unregister_component() { this->get_game_core()->get_physics_component_manager()->unregister_component(this); }
