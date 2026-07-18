
#include "components/behavior_components/player_animation_component.hpp"

#include <raylib.h>

#include "components/behavior_components/animation_component.hpp"
#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/button_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

PlayerAnimationComponent::PlayerAnimationComponent(Handle<Entity> entity) : AnimationComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_physics_component = entity->get_component<PhysicsComponent>();

    if (DEBUG_ERROR && this->_physics_component.is_null()) {
        // TODO: Standardize this error and warning prints
        log_error(this, "PlayerAnimationComponent: _physics_component is null");
    }

    this->register_animation<PlayerAnimationComponent>(
        IDLE, this->make_handle<PlayerAnimationComponent>(), &PlayerAnimationComponent::_run, 1.0);

    this->register_animation<PlayerAnimationComponent>(
        FLIP_LEFT, this->make_handle<PlayerAnimationComponent>(), &PlayerAnimationComponent::_flip_left);

    this->register_animation<PlayerAnimationComponent>(
        FLIP_RIGHT, this->make_handle<PlayerAnimationComponent>(), &PlayerAnimationComponent::_flip_right);
}
