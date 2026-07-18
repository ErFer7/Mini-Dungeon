#include "components/behavior_components/animation_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/button_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

AnimationComponent::AnimationComponent(Handle<Entity> entity)
    : BehaviorComponent(entity),
      _current_animation_state(IDLE) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_graphics_component = entity->get_component<GraphicsComponent>();

    if (DEBUG_ERROR && this->_graphics_component.is_null()) {
        // TODO: Standardize this error and warning prints
        log_error(this, "AnimationComponent: _graphics_component is null");
    }
}
