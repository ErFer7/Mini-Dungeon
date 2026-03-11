#include "gameplay/dungeon.hpp"

#include <format>
#include <fstream>
#include <random>

#include "containers/entity_container.hpp"
#include "definitions.hpp"
#include "entities/gameplay/tiles.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "game_core.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

Dungeon::Room::Room(std::string room_path, bool top_door, bool bottom_door, bool left_door, bool right_door) {
    this->_tiles = std::make_unique<TileVector>();

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
    std::uniform_int_distribution<int> distribution(0, max_index);

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
                    this->_create_tile("assets/sprites/walls/wall_top_left.png", position, true, true, TOP_LEFT);
                    break;
                case '_':
                    this->_create_tile("assets/sprites/walls/wall_top.png", position, true, true, TOP);
                    break;
                case '&':
                    this->_create_tile("assets/sprites/walls/wall_top_right.png", position, true, true, TOP_RIGHT);
                    break;
                case '$':
                    this->_create_tile("assets/sprites/walls/wall_left.png", position, true, true, LEFT);
                    break;
                case '#': {
                    int index = distribution(generator);
                    this->_create_tile(std::format("assets/sprites/walls/wall_{}.png", index), position, true);
                    break;
                }
                case '%':
                    this->_create_tile("assets/sprites/walls/wall_right.png", position, true, true, RIGHT);
                    break;
                case '+':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_left_new.png", position, true, true, BOTTOM_LEFT);
                    break;
                case '=':
                    this->_create_tile("assets/sprites/walls/wall_bottom_new.png", position, true);
                    break;
                case '-':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_right_new.png", position, true, true, BOTTOM_RIGHT);
                    break;
                case '.':
                    this->_create_tile("", position, true, true, BOTTOM);
                    break;
                case 'q':
                    this->_create_tile("assets/sprites/floors/floor_top_left.png", position, false);
                    break;
                case '^':
                    this->_create_tile("assets/sprites/floors/floor_top.png", position, false);
                    break;
                case 'w':
                    this->_create_tile("assets/sprites/floors/floor_top_right.png", position, false);
                    break;
                case '<':
                    this->_create_tile("assets/sprites/floors/floor_left.png", position, false);
                    break;
                case '\'':
                    this->_create_tile("assets/sprites/floors/floor.png", position, false);
                    break;
                case '>':
                    this->_create_tile("assets/sprites/floors/floor_right.png", position, false);
                    break;
                case 'e':
                    this->_create_tile("assets/sprites/floors/floor_bottom_left.png", position, false);
                    break;
                case 'v':
                    this->_create_tile("assets/sprites/floors/floor_bottom.png", position, false);
                    break;
                case 'r':
                    this->_create_tile("assets/sprites/floors/floor_bottom_right.png", position, false);
                    break;
                case 't':
                    this->_create_tile("assets/sprites/floors/floor_detailed_top.png", position, false);
                    break;
                case 'i':
                    this->_create_tile("assets/sprites/floors/floor_detailed_left.png", position, false);
                    break;
                case 'y':
                    this->_create_tile("assets/sprites/floors/floor_detailed_right.png", position, false);
                    break;
                case 'u':
                    this->_create_tile("assets/sprites/floors/floor_detailed_bottom.png", position, false);
                    break;
                case ';':
                    this->_create_tile("assets/sprites/obstacles/box.png", position, true, true, CENTER);
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

void Dungeon::Room::_create_tile(std::string sprite_path,
                                 Vector2Df position,
                                 bool wall_level,
                                 bool has_collider,
                                 Direction collider_direction) {
    Texture2D texture =
        sprite_path.empty() ? Texture2D() : GameCore::get_texture_container()->load_texture(sprite_path);

    Handle<Entity2D> tile;

    if (!wall_level) {
        tile = static_cast<Handle<Floor>>(GameCore::get_entity_container()->create_entity<Floor>(Entity2DArgs{
            .texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position, .layer = -1}));

        this->_tiles->push_back(tile);

        return;
    }

    if (!has_collider) {
        tile = static_cast<Handle<BackgroundWall>>(GameCore::get_entity_container()->create_entity<BackgroundWall>(
            Entity2DArgs{.texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position}));

        this->_tiles->push_back(tile);

        return;
    }

    Rectangle collider_rectangle;
    const float size = BASE_SIZE * VIRTUAL_SCALE;

    switch (collider_direction) {
        case TOP_LEFT:
            collider_rectangle = Rectangle{size / 4.0f, -size / 4.0f, size / 2.0f, size / 2.0f};
            break;
        case TOP:
            collider_rectangle = Rectangle{0.0f, -size / 4.0f, size, size / 1.25f};
            break;
        case TOP_RIGHT:
            collider_rectangle = Rectangle{-size / 4.0f, -size / 4.0f, size / 2.0f, size / 2.0f};
            break;
        case LEFT:
            collider_rectangle = Rectangle{size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case CENTER:
            collider_rectangle = Rectangle{0.0f, -size / 4.0f, size, size / 2.0f};
            break;
        case RIGHT:
            collider_rectangle = Rectangle{-size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case BOTTOM_LEFT:
            collider_rectangle = Rectangle{size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case BOTTOM:
            collider_rectangle = Rectangle{0.0f, size / 4.0f, size, size / 2.0f};
            break;
        case BOTTOM_RIGHT:
            collider_rectangle = Rectangle{-size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        default:
            break;
    }

    tile = static_cast<Handle<Wall>>(GameCore::get_entity_container()->create_entity<Wall>(
        StaticPhysicalEntity2DArgs{.texture = texture,
                                   .rendering_mode = RenderingMode::WORLD_SPACE_2D,
                                   .position = position,
                                   .collider_rectangle = collider_rectangle}));

    this->_tiles->push_back(tile);
}
