#include "../../../include/entities/user_interface/text.hpp"

#include "entities/user_interface/ui_entity.hpp"
#include "raylib.h"

Text::Text(GameCore *game_core,
           string content,
           Font font,
           UIOrigin ui_origin,
           int font_size,
           Vector2 position,
           float rotation,
           Vector2 scale,
           Color color,  // TODO: It might be better to have two colors, one for the graphics component and one for the text
           int layer,
           UITransformComponent *parent_ui_transform,
           float spacing)
    : UIEntity(game_core, Texture2D(), ui_origin, position, rotation, scale, WHITE, layer, parent_ui_transform) {
    this->_text_component = this->create_component<TextComponent>(content, font, font_size, spacing, color);
}