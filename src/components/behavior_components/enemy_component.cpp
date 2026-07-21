#include "components/behavior_components/enemy_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/player_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"
#include "entities/gameplay/player.hpp"

EnemyComponent::EnemyComponent(Handle<Entity> entity, const EnemyComponentArgs &args)
    : CharacterComponent(entity, args) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_player = args.player;
}

void EnemyComponent::update() {
    Vector2Df diff =
        this->_player->get_transform_component()->get_position() - this->transform_component()->get_position();

    // TODO: Add constants
    if (diff.magnitude() > 500.0f) {
        return;
    }

    this->physics_component()->set_velocity(diff.normalized() * ENEMY_SPEED);

    if (diff.x > 0.0f) {
        this->walking_animation_component()->run_instantaneous_animation(WalkingAnimationComponent::FLIP_LEFT);
    } else if (diff.x < 0.0f) {
        this->walking_animation_component()->run_instantaneous_animation(WalkingAnimationComponent::FLIP_RIGHT);
    }
}

void EnemyComponent::_move(EnemyComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_player = std::move(other._player);
}
