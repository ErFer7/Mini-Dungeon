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

// FIX: This is terrible. The room file needs to be redesigned
Room::Room(std::string room_path,
           const std::tuple<bool, bool, bool, bool> &door_connections,
           Dungeon *dungeon,
           Handle<Player> player) {
    this->_tiles = std::make_unique<TileVector>();
    this->_enemies = std::make_unique<EnemyVector>();

    const float tile_size = BASE_SIZE * VIRTUAL_SCALE;
    const int max_index = 11;
    const int max_enemy_index = 24;

    std::ifstream file(room_path);

    std::string token;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int row = 0;
    unsigned int column = 0;
    bool reading_room = false;
    bool reading_info = false;
    char info_char = ' ';
    int player_row = 0;
    int player_column = 0;
    int enemy_row = 0;
    int enemy_column = 0;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(0, max_index);
    std::uniform_int_distribution<int> enemy_distribution(0, max_enemy_index);

    // TODO: Use a finite state machine
    while (file >> token) {
        if (token == "!") {
            if (reading_info) {
                this->_player_spawn = Vector2Df((player_column - width / 2.0f) * tile_size - tile_size / 2.0f,
                                                (player_row - height / 2.0f) * tile_size - tile_size / 2.0f);

                break;
            }

            reading_info = true;
            continue;
        }

        if (reading_info) {
            if (token == "P") {
                info_char = 'P';
                continue;
            }

            if (token == "E") {
                info_char = 'E';
                continue;
            }

            if (info_char == 'P') {
                if (player_column == 0) {
                    player_column = std::atoi(token.c_str());
                    continue;
                }

                if (player_row == 0) {
                    player_row = std::atoi(token.c_str());
                    continue;
                }
            }

            if (info_char == 'E') {
                if (enemy_column == 0) {
                    enemy_column = std::atoi(token.c_str());
                    continue;
                }

                if (enemy_row == 0) {
                    enemy_row = std::atoi(token.c_str());

                    int index = enemy_distribution(generator);

                    Texture2D enemy_texture = GameCore::get_texture_container()->load_texture(
                        std::format("assets/sprites/monsters/Monster_{}.png", index));

                    Handle<Enemy> enemy = GameCore::get_entity_container()->create_entity<Enemy>(EnemyArgs{
                        .texture = enemy_texture,
                        .rendering_mode = RenderingMode::WORLD_SPACE_2D,
                        .player = player,
                        .max_health = 75,
                        .position = Vector2Df((enemy_column - width / 2.0f) * tile_size - tile_size / 2.0f,
                                              (enemy_row - height / 2.0f) * tile_size - tile_size / 2.0f),
                        .collider_rectangle =
                            Rectangle{0.0f, 0.0f, BASE_SIZE * VIRTUAL_SCALE * 0.6f, BASE_SIZE * VIRTUAL_SCALE}});

                    this->_enemies->push_back(enemy);

                    enemy->set_active(false);

                    enemy_column = 0;
                    enemy_row = 0;

                    continue;
                }
            }

            continue;
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
                    this->_create_tile(
                        "assets/sprites/walls/wall_top_left.png", position, OBSTACLE, Direction::TOP_LEFT);
                    break;
                case '_':
                    this->_create_tile("assets/sprites/walls/wall_top.png", position, OBSTACLE, Direction::TOP);
                    break;
                case '&':
                    this->_create_tile(
                        "assets/sprites/walls/wall_top_right.png", position, OBSTACLE, Direction::TOP_RIGHT);
                    break;
                case '$':
                    this->_create_tile("assets/sprites/walls/wall_left.png", position, OBSTACLE, Direction::LEFT);
                    break;
                case '#': {
                    int index = distribution(generator);
                    this->_create_tile(std::format("assets/sprites/walls/wall_{}.png", index), position, BACKGROUND);
                    break;
                }
                case '%':
                    this->_create_tile("assets/sprites/walls/wall_right.png", position, OBSTACLE, Direction::RIGHT);
                    break;
                case '+':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_left_new.png", position, OBSTACLE, Direction::BOTTOM_LEFT);
                    break;
                case '=':
                    this->_create_tile("assets/sprites/walls/wall_bottom_new.png", position, BACKGROUND);
                    break;
                case '-':
                    this->_create_tile(
                        "assets/sprites/walls/wall_bottom_right_new.png", position, OBSTACLE, Direction::BOTTOM_RIGHT);
                    break;
                case '.':
                    this->_create_tile("", position, OBSTACLE, Direction::BOTTOM);
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
                    this->_create_tile("assets/sprites/obstacles/box.png", position, OBSTACLE);
                    break;
                case '0': {
                    if (std::get<DirectionIndex::TOP>(door_connections)) {
                        this->_doors[DirectionIndex::TOP] = static_cast<Handle<Door>>(this->_create_tile(
                            "assets/sprites/doors/door_top.png", position, DOOR, Direction::TOP, dungeon));

                        this->_entrance_positions[DirectionIndex::TOP] =
                            Vector2Df(position.x, position.y - tile_size * ENTRANCE_OFFSET);
                    } else {
                        int index = distribution(generator);
                        this->_create_tile(
                            std::format("assets/sprites/walls/wall_{}.png", index), position, BACKGROUND);
                    }
                    break;
                }
                case '1': {
                    if (std::get<DirectionIndex::BOTTOM>(door_connections)) {
                        this->_create_tile("assets/sprites/floors/floor_dark.png", position, FLOOR);
                        this->_doors[DirectionIndex::BOTTOM] = static_cast<Handle<Door>>(this->_create_tile(
                            "assets/sprites/doors/door_bottom.png", position, DOOR, Direction::BOTTOM, dungeon));

                        this->_entrance_positions[DirectionIndex::BOTTOM] =
                            Vector2Df(position.x, position.y + tile_size * ENTRANCE_OFFSET);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_bottom_new.png", position, BACKGROUND);
                    }
                    break;
                }
                // FIX: The numbers don't match
                case '2': {
                    if (std::get<DirectionIndex::RIGHT>(door_connections)) {
                        this->_doors[DirectionIndex::RIGHT] = static_cast<Handle<Door>>(this->_create_tile(
                            "assets/sprites/doors/door_right.png", position, DOOR, Direction::RIGHT, dungeon));

                        this->_entrance_positions[DirectionIndex::RIGHT] =
                            Vector2Df(position.x - tile_size * ENTRANCE_OFFSET, position.y);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_right.png", position, OBSTACLE, Direction::RIGHT);
                    }
                    break;
                }
                case '3': {
                    if (std::get<DirectionIndex::LEFT>(door_connections)) {
                        this->_doors[DirectionIndex::LEFT] = static_cast<Handle<Door>>(this->_create_tile(
                            "assets/sprites/doors/door_left.png", position, DOOR, Direction::LEFT, dungeon));

                        this->_entrance_positions[DirectionIndex::LEFT] =
                            Vector2Df(position.x + tile_size * ENTRANCE_OFFSET, position.y);
                    } else {
                        this->_create_tile("assets/sprites/walls/wall_left.png", position, OBSTACLE, Direction::LEFT);
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

void Room::set_active(bool active) {
    for (auto &tile : *this->_tiles) {
        tile->set_active(active);
    }

    for (auto &enemy : *this->_enemies) {
        enemy->set_active(active);
    }
}

void Room::connect_to_room(Room *other, const DirectionIndex &direction_index) {
    this->_doors[direction_index]->get_door_component()->set_exit(
        other, other->entrance_positions(direct_opposite(direction_index)));
}

Handle<Entity2D> Room::_create_tile(std::string sprite_path,
                                    Vector2Df position,
                                    TileType tile_type,
                                    Direction tile_collider_direction,
                                    Dungeon *dungeon) {
    Texture2D texture =
        sprite_path.empty() ? Texture2D() : GameCore::get_texture_container()->load_texture(sprite_path);

    Handle<Entity2D> tile;

    if (tile_type == FLOOR) {
        tile = static_cast<Handle<Floor>>(GameCore::get_entity_container()->create_entity<Floor>(Entity2DArgs{
            .texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position, .layer = -1}));

        // TODO: Allow entities to be created inactive
        tile->set_active(false);

        this->_tiles->push_back(tile);

        return tile;
    }

    if (tile_type == BACKGROUND) {
        tile = static_cast<Handle<BackgroundWall>>(GameCore::get_entity_container()->create_entity<BackgroundWall>(
            Entity2DArgs{.texture = texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = position}));

        tile->set_active(false);

        this->_tiles->push_back(tile);

        return tile;
    }

    Rectangle collider_rectangle;
    const float size = BASE_SIZE * VIRTUAL_SCALE;

    switch (tile_collider_direction) {
        case Direction::TOP_LEFT:
            collider_rectangle = Rectangle{size / 4.0f, -size / 4.0f, size / 2.0f, size / 2.0f};
            break;
        case Direction::TOP:
            collider_rectangle = Rectangle{0.0f, -size / 4.0f, size, size / 1.25f};
            break;
        case Direction::TOP_RIGHT:
            collider_rectangle = Rectangle{-size / 4.0f, -size / 4.0f, size / 2.0f, size / 2.0f};
            break;
        case Direction::LEFT:
            collider_rectangle = Rectangle{size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case Direction::CENTER:
            collider_rectangle = Rectangle{0.0f, -size / 4.0f, size, size / 2.0f};
            break;
        case Direction::RIGHT:
            collider_rectangle = Rectangle{-size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case Direction::BOTTOM_LEFT:
            collider_rectangle = Rectangle{size / 4.0f, 0.0f, size / 2.0f, size};
            break;
        case Direction::BOTTOM:
            collider_rectangle = Rectangle{0.0f, size / 4.0f, size, size / 2.0f};
            break;
        case Direction::BOTTOM_RIGHT:
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
                                       .collision_group = OBSTACLE,
                                       .collider_rectangle = collider_rectangle}));
    } else {
        utils::log_info(this, "Door created");
        tile = static_cast<Handle<Door>>(GameCore::get_entity_container()->create_entity<Door>(
            DoorArgs{.texture = texture,
                     .rendering_mode = RenderingMode::WORLD_SPACE_2D,
                     .position = position,
                     .collider_rectangle = collider_rectangle,
                     .dungeon = dungeon}));
    }

    tile->set_active(false);

    this->_tiles->push_back(tile);

    return tile;
}
