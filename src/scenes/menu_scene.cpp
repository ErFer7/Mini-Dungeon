#include "scenes/menu_scene.hpp"

#include <raylib.h>

#include "components/behavior_components/button_component.hpp"
#include "components/ui_transform_component.hpp"
#include "containers/asset_containers/font_container.hpp"
#include "containers/entity_container.hpp"
#include "entities/user_interface/text.hpp"
#include "entities/user_interface/text_button.hpp"
#include "game_core.hpp"
#include "managers/game_manager.hpp"

void MenuScene::init() {
    GameCore *game_core = GameCore::get_instance();
    EntityContainer *entity_container = game_core->get_entity_container();
    FontContainer *font_container = game_core->get_font_container();

    this->_background = entity_container->create_entity<Background>();

    Font title_font = font_container->load_font("title", "assets/fonts/joystix monospace.ttf", 80);
    Font button_font = font_container->load_font("button", "assets/fonts/joystix monospace.ttf", 40);
    Font small_font = font_container->load_font("small", "assets/fonts/joystix monospace.ttf", 20);

    GenTextureMipmaps(&title_font.texture);
    SetTextureFilter(title_font.texture, TEXTURE_FILTER_POINT);

    Color golden = Color{255, 223, 0, 255};
    Color dark = Color{20, 20, 20, 255};

    Image button_image = GenImageColor(400, 100, golden);
    ImageDrawRectangle(&button_image, 10, 10, 380, 80, dark);

    // TODO: Cache this
    this->_button_texture = LoadTextureFromImage(button_image);

    UnloadImage(button_image);

    this->_title = entity_container->create_entity<Text>(TextArgs{.content = "Mini Dungeon",
                                                                  .font = title_font,
                                                                  .ui_origin = UIOrigin::CENTER,
                                                                  .position = Vector2Df(0.0f, -200.0f),
                                                                  .color = golden});
    this->_version = entity_container->create_entity<Text>(TextArgs{
        .content = "v2.0",
        .font = small_font,
        .ui_origin = UIOrigin::TOP_LEFT,
        .position = Vector2Df(35.0f, 15.0f)  // TODO: Fix the position
    });
    this->_play_button = entity_container->create_entity<TextButton>(TextButtonArgs{.texture = this->_button_texture,
                                                                                    .ui_origin = UIOrigin::CENTER,
                                                                                    .content = "PLAY",
                                                                                    .font = button_font,
                                                                                    .text_color = golden});
    this->_exit_button = entity_container->create_entity<TextButton>(TextButtonArgs{.texture = this->_button_texture,
                                                                                    .ui_origin = UIOrigin::CENTER,
                                                                                    .content = "QUIT",
                                                                                    .font = button_font,
                                                                                    .position = Vector2Df(0.0f, 200.0f),
                                                                                    .text_color = golden});

    this->_play_listener.set_callable(
        [this]() { GameCore::get_instance()->get_game_manager()->transition_to_gameplay(); });
    this->_play_listener.subscribe(this->_play_button->get_button_component()->get_on_click_event());

    this->_exit_listener.set_callable([this]() { GameCore::get_instance()->exit(); });
    this->_exit_listener.subscribe(this->_exit_button->get_button_component()->get_on_click_event());

    this->_was_initialized = true;
}

void MenuScene::leave() {
    this->_background->set_active(false);
    this->_title->set_active(false);
    this->_version->set_active(false);
    this->_play_button->set_active(false);
    this->_exit_button->set_active(false);
}

void MenuScene::exit() { UnloadTexture(this->_button_texture); }
