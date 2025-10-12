#include "components/behavior_components/button_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "definitions.hpp"

ButtonComponent::ButtonComponent(GameCore *game_core, Entity *entity) : BehaviorComponent(game_core, entity) {
    log_info("ButtonComponent::ButtonComponent(", game_core, ", ", entity, ')');

    this->_graphics_component = entity->get_component<GraphicsComponent>();

    if (DEBUG_ERROR && this->_graphics_component == nullptr) {
        log_error("ButtonComponent [", this, "] -> _graphics_component is null");
    }
}

void ButtonComponent::update() {
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
