#include "entities/user_interface/button.hpp"

#include "entities/user_interface/ui_entity.hpp"

Button::Button(const ButtonArgs &args) : UIEntity(static_cast<UIEntityArgs>(args)) {
    this->_button_component = this->create_component<ButtonComponent>();
}
