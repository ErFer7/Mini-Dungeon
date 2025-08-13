#include "../../include/scenes/main_menu_scene.hpp"

#include "../../include/components/ui_transform_component.hpp"
#include "../../include/game_core.hpp"
#include "raylib.h"
#include "raymath.h"

void MainMenuScene::init() {
    this->_background = this->get_game_core()->get_entity_container()->create_entity<Background>();

    Font title_font = this->get_game_core()->get_asset_container()->load_font("title", "assets/fonts/joystix monospace.ttf", 80);
    Font small_font = this->get_game_core()->get_asset_container()->load_font("small", "assets/fonts/joystix monospace.ttf", 20);

    GenTextureMipmaps(&title_font.texture);
    SetTextureFilter(title_font.texture, TEXTURE_FILTER_POINT);

    this->_title = this->get_game_core()->get_entity_container()->create_entity<Text>(
        "Mini Dungeon", title_font, UIOrigin::CENTER, 0, Vector2{0.0f, -200.0f}, 0.0f, Vector2One(), Color{255, 223, 0, 255});
    this->_version = this->get_game_core()->get_entity_container()->create_entity<Text>(
        "v2.0", small_font, UIOrigin::TOP_LEFT, 0, Vector2{35.0f, 15.0f});  // TODO: Fix the position
}

void MainMenuScene::exit() {}
