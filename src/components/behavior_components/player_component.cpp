#include "components/behavior_components/player_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/player_animation_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

PlayerComponent::PlayerComponent(Handle<Entity> entity) : BehaviorComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_transform_component = entity->get_component<TransformComponent>();
    this->_physics_component = entity->get_component<PhysicsComponent>();
    this->_player_animation_component = entity->get_component<PlayerAnimationComponent>();
}

void PlayerComponent::update() {
    GameCore::get_graphics_manager()->set_camera_position(this->_transform_component->get_position());

    if (IsKeyDown(KEY_UP)) {
        this->_physics_component->set_velocity_y(PLAYER_SPEED);
    } else if (IsKeyDown(KEY_DOWN)) {
        this->_physics_component->set_velocity_y(-PLAYER_SPEED);
    }

    // TODO: Implement the animation system
    if (IsKeyDown(KEY_RIGHT)) {
        this->_physics_component->set_velocity_x(PLAYER_SPEED);
        this->_player_animation_component->run_instantaneous_animation(PlayerAnimationComponent::FLIP_RIGHT);
    } else if (IsKeyDown(KEY_LEFT)) {
        this->_physics_component->set_velocity_x(-PLAYER_SPEED);
        this->_player_animation_component->run_instantaneous_animation(PlayerAnimationComponent::FLIP_LEFT);
    }
}

void PlayerComponent::_move(PlayerComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_physics_component = std::move(other._physics_component);
}
