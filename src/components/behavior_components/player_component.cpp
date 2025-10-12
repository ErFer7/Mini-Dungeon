#include "components/behavior_components/player_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"

PlayerComponent::PlayerComponent(GameCore *game_core, Entity *entity) : BehaviorComponent(game_core, entity) {
    this->_physics_component = entity->get_component<PhysicsComponent>();
}

void PlayerComponent::update() {
    Vector2Df velocity = Vector2Df();
    float player_speed = PLAYER_SPEED;

    if (IsKeyDown(KEY_UP)) {
        velocity += Vector2Df(0.0f, player_speed);
    } else if (IsKeyDown(KEY_DOWN)) {
        velocity += Vector2Df(0.0f, -player_speed);
    }

    if (IsKeyDown(KEY_RIGHT)) {
        velocity += Vector2Df(player_speed, 0.0f);
    } else if (IsKeyDown(KEY_LEFT)) {
        velocity += Vector2Df(-player_speed, 0.0f);
    }

    if (!velocity.is_zero()) {
        this->_physics_component->set_velocity(velocity);
    }
}
