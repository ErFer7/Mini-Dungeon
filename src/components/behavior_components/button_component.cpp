#include "components/behavior_components/button_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

ButtonComponent::ButtonComponent(Handle<Entity> entity) : BehaviorComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_graphics_component = entity->get_component<GraphicsComponent>();

    if (DEBUG_ERROR && this->_graphics_component.is_null()) {
        // TODO: Standardize this error and warning prints
        log_error(this, "ButtonComponent: _graphics_component is null");
    }
}

void ButtonComponent::update() {
    if constexpr (DEBUGGED_ON_LOOP) {
        log_trace(this, __PRETTY_FUNCTION__);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_position = GetMousePosition();
        Rectangle button_rect = this->_graphics_component->get_rectangle();

        if (CheckCollisionPointRec(mouse_position, button_rect)) {
            log_info(this,
                     "ButtonComponent: Button clicked with mouse position on {",
                     mouse_position.x,
                     ", ",
                     mouse_position.y,
                     '}');

            this->_on_click_event.invoke();
        }
    }
}
