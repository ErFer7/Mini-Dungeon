#include "entities/user_interface/text.hpp"

#include "components/text_component.hpp"
#include "entities/user_interface/ui_entity.hpp"

Text::Text(GameCore *game_core, const TextArgs &args) : UIEntity(game_core, static_cast<UIEntityArgs>(args)) {
    this->_text_component = this->create_component<TextComponent>(static_cast<TextComponentArgs>(args));
}