#include "components/behavior_components/button_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"

ButtonComponent::ButtonComponent(GameCore *game_core, Entity *entity) : BehaviorComponent(game_core, entity) {
    this->_graphics_component = entity->get_component<GraphicsComponent>();
}

void ButtonComponent::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_position = GetMousePosition();
        Rectangle button_rect = this->_graphics_component->get_rectangle();

        if (CheckCollisionPointRec(mouse_position, button_rect)) {
            this->_on_click_event.invoke();
        }
    }
}
