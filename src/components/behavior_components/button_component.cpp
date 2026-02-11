#include "components/behavior_components/button_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

ButtonComponent::ButtonComponent(Entity *entity) : BehaviorComponent(entity) {
    utils::log_info(__FUNCTION__, '(', entity, ')');

    this->_graphics_component = entity->get_component<GraphicsComponent>();

    if (DEBUG_ERROR && this->_graphics_component.is_null()) {
        log_error("ButtonComponent [", this, "] -> _graphics_component is null");
    }
}

void ButtonComponent::update() {
    // TODO: Create a log_loop_info for this
    if constexpr (DEBUGGED_ON_LOOP) {
        log_info("ButtonComponent::update()");
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_position = GetMousePosition();
        Rectangle button_rect = this->_graphics_component->get_rectangle();

        if (CheckCollisionPointRec(mouse_position, button_rect)) {
            log_info("ButtonComponent [",
                     this,
                     "] -> Button clicked with mouse position on {",
                     mouse_position.x,
                     ", ",
                     mouse_position.y,
                     '}');

            this->_on_click_event.invoke();
        }
    }
}
