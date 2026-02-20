#include "gameplay/dungeon.hpp"

#include <format>
#include <fstream>
#include <random>

#include "containers/entity_container.hpp"
#include "definitions.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "game_core.hpp"

Dungeon::Room::Room(std::string room_path, bool top_door, bool bottom_door, bool left_door, bool right_door) {
    this->_walls = std::make_unique<WallVector>();

    const float tile_size = BASE_SIZE * VIRTUAL_SCALE;
    const int max_index = 11;

    std::ifstream file(room_path);

    std::string token;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int row = 0;
    unsigned int column = 0;
    bool reading_room = false;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(0, 11);

    // TODO: Use a finite state machine
    while (file >> token) {
        if (token == "!") {
            break;
        }

        if (width == 0) {
            width = std::atoi(token.c_str());
        }

        if (height == 0) {
            height = std::atoi(token.c_str());
            reading_room = true;
        }

        column = 0;

        for (char &character : token) {
            Vector2Df position = Vector2Df((column - width / 2.0f) * tile_size - tile_size / 2.0f,
                                           -((row - height / 2.0f) * tile_size - tile_size / 2.0f));

            switch (character) {
                case '@':
                    this->_create_wall("assets/sprites/walls/wall_top_left.png", position);
                    break;
                case '_': {
                    this->_create_wall("assets/sprites/walls/wall_top.png", position);
                    break;
                }
                case '&':
                    this->_create_wall("assets/sprites/walls/wall_top_right.png", position);
                    break;
                case '$':
                    this->_create_wall("assets/sprites/walls/wall_left.png", position);
                    break;
                case '#': {
                    int index = distribution(generator);
                    this->_create_wall(std::format("assets/sprites/walls/wall_{}.png", index), position);
                    break;
                }
                case '%':
                    this->_create_wall("assets/sprites/walls/wall_right.png", position);
                    break;
                case '+':
                    this->_create_wall("assets/sprites/walls/wall_bottom_left.png", position);
                    break;
                case '=':
                    this->_create_wall("assets/sprites/walls/wall_bottom.png", position);
                    break;
                case '-':
                    this->_create_wall("assets/sprites/walls/wall_bottom_right.png", position);
                    break;
                default:
                    log_warn(this, "Room: Invalid tile: ", character);
                    break;
            }

            column++;
        }

        if (reading_room) {
            row++;
        }
    }
}

void Dungeon::Room::_create_wall(std::string sprite_path, Vector2Df position) {
    Texture2D texture = GameCore::get_instance()->get_texture_container()->load_texture(sprite_path);

    Handle<Wall> wall =
        GameCore::get_instance()->get_entity_container()->create_entity<Wall>(StaticPhysicalEntity2DArgs{
            .texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position});

    this->_walls->push_back(wall);
}
