#include "entities/user_interface/text_button.hpp"

#include "containers/entity_container.hpp"
#include "entities/user_interface/button.hpp"
#include "entities/user_interface/text.hpp"
#include "game_core.hpp"

TextButton::TextButton(const TextButtonArgs &args) : Button(static_cast<ButtonArgs>(args)) {
    TextArgs text_args = static_cast<TextArgs>(args);

    text_args.parent_ui_transform = this->get_ui_transform_component();
    text_args.parent_activity_state = this->get_activity_state();

    this->_text = GameCore::get_entity_container()->create_entity<Text>(text_args);
}

TextButton::~TextButton() { GameCore::get_entity_container()->destroy_entity(this->_text); }
