#include "../../../include/entities/user_interface/text_button.hpp"

#include "../../../include/game_core.hpp"
#include "components/text_component.hpp"
#include "entities/user_interface/button.hpp"

TextButton::TextButton(GameCore *game_core, const TextButtonArgs &args)
    : Button(game_core,
             ButtonArgs{args.texture,
                        args.ui_origin,
                        args.position,
                        args.rotation,
                        args.scale,
                        args.color,
                        args.layer,
                        args.parent_ui_transform,
                        args.parent_activity_state}) {
    this->_text = this->get_game_core()->get_entity_container()->create_entity<Text>(TextArgs{args.content,
                                                                                              args.font,
                                                                                              args.text_ui_origin,
                                                                                              args.font_size,
                                                                                              args.text_position,
                                                                                              args.text_rotation,
                                                                                              args.text_scale,
                                                                                              args.text_color,
                                                                                              0,
                                                                                              this->get_ui_transform_component(),
                                                                                              args.spacing,
                                                                                              this->get_activity_state()});
}

TextButton::~TextButton() { this->get_game_core()->get_entity_container()->destroy_entity(this->_text); }