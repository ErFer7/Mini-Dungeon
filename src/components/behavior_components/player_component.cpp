#include "components/behavior_components/player_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"
#include "entities/gameplay/sword.hpp"

PlayerComponent::PlayerComponent(Handle<Entity> entity, const PlayerComponentArgs &args)
    : CharacterComponent(entity, args),
      _sword(args.sword) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_sword->set_active(false);
}

void PlayerComponent::update() {
    GameCore::get_graphics_manager()->set_camera_position(this->transform_component()->get_position());

    if (IsKeyDown(KEY_UP)) {
        this->physics_component()->set_velocity_y(PLAYER_SPEED);
    } else if (IsKeyDown(KEY_DOWN)) {
        this->physics_component()->set_velocity_y(-PLAYER_SPEED);
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->physics_component()->set_velocity_x(PLAYER_SPEED);
        this->walking_animation_component()->run_instantaneous_animation(WalkingAnimationComponent::FLIP_RIGHT);
    } else if (IsKeyDown(KEY_LEFT)) {
        this->physics_component()->set_velocity_x(-PLAYER_SPEED);
        this->walking_animation_component()->run_instantaneous_animation(WalkingAnimationComponent::FLIP_LEFT);
    }

    if (IsKeyDown(KEY_K)) {
        this->_sword->set_active(true);
    }
}
