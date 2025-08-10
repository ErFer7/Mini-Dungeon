#include "../../include/scenes/main_menu_scene.hpp"

#include "../../include/components/ui_transform_component.hpp"
#include "../../include/game_core.hpp"
#include "raylib.h"
#include "raymath.h"

void MainMenuScene::init() {
    Font font = LoadFont("assets/fonts/joystix monospace.ttf");

    this->_title = this->get_game_core()->get_entity_container()->create_entity<Text>(UIOrigin::CENTER, "Test", font, 40);

    this->_title->get_ui_transform_component()->set_position(Vector2Zero());
}

void MainMenuScene::exit() { UnloadFont(this->_title->get_text_component()->get_font()); }
