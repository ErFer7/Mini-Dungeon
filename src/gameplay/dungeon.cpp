#include "gameplay/dungeon.hpp"

#include <format>
#include <fstream>
#include <random>

#include "containers/entity_container.hpp"
#include "definitions.hpp"
#include "entities/gameplay/door.hpp"
#include "entities/gameplay/tiles.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "game_core.hpp"
#include "raylib.h"
#include "utils/debug.hpp"

Dungeon::Room::Room(std::string room_path, Dungeon::DoorMap door_map) {
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
            continue;
        }

        if (height == 0) {
            height = std::atoi(token.c_str());
            reading_room = true;
            continue;
        }

        column = 0;

        for (char &character : token) {
            Vector2Df position = Vector2Df((column - width / 2.0f) * tile_size - tile_size / 2.0f,
                                           -((row - height / 2.0f) * tile_size - tile_size / 2.0f));

            switch (character) {
                case '@':
                    this->_create_tile("assets/sprites/walls/wall_top_left.png", position, OBSTACLE, TOP_LEFT);
                    break;
                case '_':
                    this->_create_tile("assets/sprites/walls/wall_top.png", position, OBSTACLE, TOP);
                    break;
                case '&':
                    this->_create_tile("assets/sprites/walls/wall_top_right.png", position, OBSTACLE, TOP_RIGHT);
                    break;
                case '$':
                    this->_create_tile("assets/sprites/walls/wall_left.png", position, OBSTACLE, LEFT);
                    break;
                case '#': {
                    int index = distribution(generator);
                    this->_create_tile(std::format("assets/sprites/walls/wall_{}.png", index), position, BACKGROUND);
                    break;
                }
                case '%':
                    this->_create_tile("assets/sprites/walls/wall_right.png", position, OBSTACLE, RIGHT);
                    break;
                case '+':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_left_new.png", position, OBSTACLE, BOTTOM_LEFT);
                    break;
                case '=':
                    this->_create_tile("assets/sprites/walls/wall_bottom_new.png", position, BACKGROUND);
                    break;
                case '-':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_right_new.png", position, OBSTACLE, BOTTOM_RIGHT);
                    break;
                case '.':
                    this->_create_tile("", position, OBSTACLE, BOTTOM);
                    break;
                case 'q':
                    this->_create_tile("assets/sprites/floors/floor_top_left.png", position, FLOOR);
                    break;
                case '^':
                    this->_create_tile("assets/sprites/floors/floor_top.png", position, FLOOR);
                    break;
                case 'w':
                    this->_create_tile("assets/sprites/floors/floor_top_right.png", position, FLOOR);
                    break;
                case '<':
                    this->_create_tile("assets/sprites/floors/floor_left.png", position, FLOOR);
                    break;
                case '\'':
                    this->_create_tile("assets/sprites/floors/floor.png", position, FLOOR);
                    break;
                case '>':
                    this->_create_tile("assets/sprites/floors/floor_right.png", position, FLOOR);
                    break;
                case 'e':
                    this->_create_tile("assets/sprites/floors/floor_bottom_left.png", position, FLOOR);
                    break;
                case 'v':
                    this->_create_tile("assets/sprites/floors/floor_bottom.png", position, FLOOR);
                    break;
                case 'r':
                    this->_create_tile("assets/sprites/floors/floor_bottom_right.png", position, FLOOR);
                    break;
                case 't':
                    this->_create_tile("assets/sprites/floors/floor_detailed_top.png", position, FLOOR);
                    break;
                case 'i':
                    this->_create_tile("assets/sprites/floors/floor_detailed_left.png", position, FLOOR);
                    break;
                case 'y':
                    this->_create_tile("assets/sprites/floors/floor_detailed_right.png", position, FLOOR);
                    break;
                case 'u':
                    this->_create_tile("assets/sprites/floors/floor_detailed_bottom.png", position, FLOOR);
                    break;
                case ';':
                    this->_create_tile("assets/sprites/obstacles/box.png", position, OBSTACLE, CENTER);
                    break;
                case '0': {
                    if (door_map.top) {
                        this->_create_tile("assets/sprites/doors/door_top.png", position, DOOR, TOP);
                    } else {
                        int index = distribution(generator);
                        this->_create_tile(
                            std::format("assets/sprites/walls/wall_{}.png", index), position, BACKGROUND);
                    }
                    break;
                }
                case '1': {
                    if (door_map.bottom) {
                        this->_create_tile("assets/sprites/floors/floor_dark.png", position, FLOOR);
                        this->_create_tile("assets/sprites/doors/door_bottom.png", position, DOOR, BOTTOM);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_bottom_new.png", position, BACKGROUND);
                    }
                    break;
                }
                case '2': {
                    if (door_map.right) {
                        this->_create_tile("assets/sprites/doors/door_right.png", position, DOOR, RIGHT);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_right.png", position, OBSTACLE, RIGHT);
                    }
                    break;
                }
                case '3': {
                    if (door_map.left) {
                        this->_create_tile("assets/sprites/doors/door_left.png", position, DOOR, LEFT);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_left.png", position, OBSTACLE, LEFT);
                    }
                    break;
                }
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

void Dungeon::Room::set_active(bool active) {
    for (auto &tile : *this->_tiles) {
        tile->set_active(active);
    }
}

void Dungeon::Room::connect_to_room(Room *other) {}

void Dungeon::Room::_create_tile(std::string sprite_path,
                                 Vector2Df position,
                                 TileType tile_type,
                                 TileColliderDirection tile_collider_direction) {
    Texture2D texture =
        sprite_path.empty() ? Texture2D() : GameCore::get_texture_container()->load_texture(sprite_path);

    Handle<Entity2D> tile;

    if (tile_type == FLOOR) {
        tile = static_cast<Handle<Floor>>(GameCore::get_entity_container()->create_entity<Floor>(Entity2DArgs{
            .texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position, .layer = -1}));

        // TODO: Allow entities to be created inactive
        tile->set_active(false);

        this->_tiles->push_back(tile);

        return;
    }

    if (tile_type == BACKGROUND) {
        tile = static_cast<Handle<BackgroundWall>>(GameCore::get_entity_container()->create_entity<BackgroundWall>(
            Entity2DArgs{.texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position}));

        tile->set_active(false);

        this->_tiles->push_back(tile);

        return;
    }

    Rectangle collider_rectangle;
    const float size = BASE_SIZE * VIRTUAL_SCALE;

    switch (tile_collider_direction) {
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

    if (tile_type == OBSTACLE) {
        tile = static_cast<Handle<Obstacle>>(GameCore::get_entity_container()->create_entity<Obstacle>(
            StaticPhysicalEntity2DArgs{.texture = texture,
                                       .rendering_mode = RenderingMode::WORLD_SPACE_2D,
                                       .position = position,
                                       .collider_rectangle = collider_rectangle}));
    } else {
        utils::log_info(this, "Door created");
        tile = static_cast<Handle<Door>>(GameCore::get_entity_container()->create_entity<Door>(
            DoorArgs{.texture = texture,
                     .rendering_mode = RenderingMode::WORLD_SPACE_2D,
                     .position = position,
                     .collider_rectangle = collider_rectangle}));
    }

    tile->set_active(false);

    this->_tiles->push_back(tile);
}
