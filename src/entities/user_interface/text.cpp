#include "../../../include/entities/user_interface/text.hpp"

#include "components/text_component.hpp"
#include "entities/user_interface/ui_entity.hpp"
#include "raylib.h"

Text::Text(GameCore *game_core, const TextArgs &args)
    : UIEntity(game_core,
               UIEntityArgs{Texture2D(),
                            args.ui_origin,
                            args.position,
                            args.rotation,
                            args.scale,
                            WHITE,
                            args.layer,
                            args.parent_ui_transform,
                            args.parent_activity_state}) {
    this->_text_component =
        this->create_component<TextComponent>(TextComponentArgs{args.content, args.font, args.font_size, args.spacing, args.color});
}