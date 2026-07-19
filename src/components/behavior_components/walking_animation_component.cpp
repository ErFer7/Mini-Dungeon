
#include "components/behavior_components/walking_animation_component.hpp"

#include <raylib.h>

#include "components/behavior_components/animation_component.hpp"
#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/button_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

WalkingAnimationComponent::WalkingAnimationComponent(Handle<Entity> entity) : AnimationComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_physics_component = entity->get_component<PhysicsComponent>();

    if (DEBUG_ERROR && this->_physics_component.is_null()) {
        // TODO: Standardize this error and warning prints
        log_error(this, "WalkingAnimationComponent: _physics_component is null");
    }

    this->register_animation<WalkingAnimationComponent>(
        IDLE, this->make_handle<WalkingAnimationComponent>(), &WalkingAnimationComponent::_run, 1.0);

    this->register_animation<WalkingAnimationComponent>(
        FLIP_LEFT, this->make_handle<WalkingAnimationComponent>(), &WalkingAnimationComponent::_flip_left);

    this->register_animation<WalkingAnimationComponent>(
        FLIP_RIGHT, this->make_handle<WalkingAnimationComponent>(), &WalkingAnimationComponent::_flip_right);
}
