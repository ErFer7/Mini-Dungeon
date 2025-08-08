#include "../../include/scenes/main_menu_scene.hpp"

#include "../../include/components/ui_transform_component.hpp"
#include "../../include/game_core.hpp"
#include "raylib.h"
#include "raymath.h"

void MainMenuScene::init() {
    this->_test_entity = this->get_game_core()->get_entity_container()->create_entity<UIEntity>(UIOrigin::CENTER);

    this->_test_entity->get_graphics_component()->set_texture(LoadTexture("assets/sprites/characters/Char_0.png"));
    this->_test_entity->get_ui_rect_transform_component()->set_position(Vector2Zero());
    this->_test_entity->get_ui_rect_transform_component()->set_scale(Vector2{5.0f, 5.0f});
}
