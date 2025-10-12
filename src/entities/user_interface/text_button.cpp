#include "entities/user_interface/text_button.hpp"

#include "game_core.hpp"
#include "entities/user_interface/button.hpp"
#include "entities/user_interface/text.hpp"

TextButton::TextButton(GameCore *game_core, const TextButtonArgs &args) : Button(game_core, static_cast<ButtonArgs>(args)) {
    TextArgs text_args = static_cast<TextArgs>(args);

    text_args.parent_ui_transform = this->get_ui_transform_component();
    text_args.parent_activity_state = this->get_activity_state();

    this->_text = this->get_game_core()->get_entity_container()->create_entity<Text>(text_args);
}

TextButton::~TextButton() { this->get_game_core()->get_entity_container()->destroy_entity(this->_text); }