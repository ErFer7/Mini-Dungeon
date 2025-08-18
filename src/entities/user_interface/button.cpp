#include "../../../include/entities/user_interface/button.hpp"

#include "entities/user_interface/ui_entity.hpp"

Button::Button(GameCore *game_core,
               Texture2D texture,
               UIOrigin ui_origin,
               Vector2 position,
               float rotation,
               Vector2 scale,
               Color color,
               int layer,
               UITransformComponent *parent_ui_transform)
    : UIEntity(game_core, texture, ui_origin, position, rotation, scale, color, layer, parent_ui_transform) {
    this->_button_component = this->create_component<ButtonComponent>();
}
