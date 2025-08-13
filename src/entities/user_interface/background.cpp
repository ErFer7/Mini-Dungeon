#include "../../../include/entities/user_interface/background.hpp"

#include "../../../include/definitions.hpp"
#include "../../../include/game_core.hpp"
#include "raylib.h"
#include "raymath.h"

Background::Background(GameCore *game_core)
    : UIEntity(game_core, Texture2D(), UIOrigin::CENTER, Vector2Zero(), 0.0f, Vector2One(), WHITE, -1) {
    float virtual_scale = VIRTUAL_SCALE;
    float virtual_screen_width = static_cast<float>(GetScreenWidth()) / virtual_scale;
    float virtual_screen_height = static_cast<float>(GetScreenHeight()) / virtual_scale;

    Image background = GenImageColor(static_cast<int>(virtual_screen_width), static_cast<int>(virtual_screen_height), WHITE);
    Image wall = this->get_game_core()->get_asset_container()->load_image("assets/sprites/walls/Wall_0.png");

    float wall_width = static_cast<float>(wall.width);
    float wall_height = static_cast<float>(wall.height);

    Rectangle source_rect = Rectangle{0.0f, 0.0f, wall_width, wall_height};
    Rectangle destination_rect = Rectangle{0.0f, 0.0f, wall_width, wall_height};

    for (float i = 0.0f; i < virtual_screen_height; i += wall_height) {
        for (float j = 0.0f; j < virtual_screen_width; j += wall_width) {
            destination_rect.x = j;
            destination_rect.y = i;

            ImageDraw(&background, wall, source_rect, destination_rect, WHITE);
        }
    }

    Texture2D texture = LoadTextureFromImage(background);

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);

    this->get_graphics_component()->set_texture(texture);

    UnloadImage(background);

    this->get_ui_transform_component()->set_scale(Vector2{virtual_scale, virtual_scale});
}

Background::~Background() { UnloadTexture(this->get_graphics_component()->get_texture()); }
