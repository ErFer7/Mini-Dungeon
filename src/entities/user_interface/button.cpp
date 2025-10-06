#include "../../../include/entities/user_interface/button.hpp"

#include "entities/user_interface/ui_entity.hpp"

Button::Button(GameCore *game_core, const ButtonArgs &args)
    : UIEntity(game_core,
               UIEntityArgs{args.texture,
                            args.ui_origin,
                            args.position,
                            args.rotation,
                            args.scale,
                            args.color,
                            args.layer,
                            args.parent_ui_transform,
                            args.parent_activity_state}) {
    this->_button_component = this->create_component<ButtonComponent>();
}
