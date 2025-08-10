#include "../../../include/entities/user_interface/text.hpp"

#include "entities/user_interface/ui_entity.hpp"

Text::Text(GameCore *game_core, UIOrigin ui_origin, string content, Font font, int font_size, UITransformComponent *parent_ui_transform)
    : UIEntity(game_core, ui_origin, parent_ui_transform) {
    this->_text_component = this->create_component<TextComponent>(content, font, font_size);
}