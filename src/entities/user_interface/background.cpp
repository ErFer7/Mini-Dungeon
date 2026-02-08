#include "entities/user_interface/background.hpp"

#include <raylib.h>

#include "definitions.hpp"
#include "entities/user_interface/ui_entity.hpp"
#include "game_core.hpp"

Background::Background()
    : UIEntity(UIEntityArgs{Texture2D(), UIOrigin::CENTER, Vector2Df(), 0.0f, Vector2Df(1.0f), WHITE, -1}) {
    float virtual_screen_width = static_cast<float>(GetScreenWidth()) / VIRTUAL_SCALE;
    float virtual_screen_height = static_cast<float>(GetScreenHeight()) / VIRTUAL_SCALE;

    Image background =
        GenImageColor(static_cast<int>(virtual_screen_width), static_cast<int>(virtual_screen_height), WHITE);
    Image wall = GameCore::get_instance()->get_image_container()->load_image("assets/sprites/walls/Wall_0.png");

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

    this->get_ui_transform_component()->set_scale(Vector2Df(VIRTUAL_SCALE));
}

Background::~Background() { UnloadTexture(this->get_graphics_component()->get_texture()); }
