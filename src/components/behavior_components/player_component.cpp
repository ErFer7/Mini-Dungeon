#include "components/behavior_components/player_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"

PlayerComponent::PlayerComponent(Entity *entity) : BehaviorComponent(entity) {
    this->_physics_component = entity->get_component<PhysicsComponent>();
}

void PlayerComponent::update() {
    if (IsKeyDown(KEY_UP)) {
        this->_physics_component->set_velocity_y(PLAYER_SPEED);
    } else if (IsKeyDown(KEY_DOWN)) {
        this->_physics_component->set_velocity_y(-PLAYER_SPEED);
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->_physics_component->set_velocity_x(PLAYER_SPEED);
    } else if (IsKeyDown(KEY_LEFT)) {
        this->_physics_component->set_velocity_x(-PLAYER_SPEED);
    }
}
