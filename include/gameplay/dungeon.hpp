#pragma once

#include <memory>
#include <queue>
#include <random>
#include <vector>

#include "entities/entity2D.hpp"
#include "entities/gameplay/enemy.hpp"
#include "entities/gameplay/player.hpp"
#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/direction.hpp"
#include "utils/vector.hpp"

using utils::direct_opposite;
using utils::Direction;
using utils::direction_count;
using utils::DirectionIndex;
using utils::Handle;
using utils::log_info;
using utils::log_warn;
using utils::random_directions;
using utils::Vector2Df;
using utils::Vector2Di;

// TODO: Refactor everything

// TODO: Move to another file
class Room {
   public:
    typedef std::vector<Handle<Entity2D>> TileVector;
    typedef std::vector<Handle<Enemy>> EnemyVector;

   private:
    enum TileType { FLOOR, OBSTACLE, BACKGROUND, DOOR };
    const float ENTRANCE_OFFSET = 1.25f;

   public:
    Room(std::string room_path,
         const std::tuple<bool, bool, bool, bool> &door_connections,
         Dungeon *dungeon,
         Handle<Player> player);

    Room() = default;

    ~Room() = default;

    void connect_to_room(Room *other, const DirectionIndex &direction_index);

    void set_active(bool ative);

    inline Vector2Df player_spawn() { return this->_player_spawn; }

   private:
    Handle<Entity2D> _create_tile(std::string sprite_path,
                                  Vector2Df position,
                                  TileType tile_type,
                                  Direction tile_collider_direction = Direction::CENTER,
                                  Dungeon *dungeon = nullptr);

    inline Vector2Df entrance_positions(const DirectionIndex &direction_index) {
        return this->_entrance_positions[direction_index];
    }

   private:
    std::unique_ptr<TileVector> _tiles;
    std::unique_ptr<EnemyVector> _enemies;

    // Top, Bottom, Left, Right
    Handle<Door> _doors[4];
    Vector2Df _entrance_positions[4];
    Vector2Df _player_spawn;
};

class Dungeon {
   public:
    typedef std::vector<std::unique_ptr<Room>> RoomVector;

   private:
    struct DoorMap {
        DoorMap *connections[4];  // Top, Bottom, Left, Right
        Direction available_directions;
        unsigned int remaining_rooms;
        Room *room;

        DoorMap() : remaining_rooms(0), available_directions(Direction::ALL), room(nullptr) {
            for (unsigned int i = 0; i < 4; i++) {
                connections[i] = nullptr;
            }
        }

        inline std::tuple<bool, bool, bool, bool> valid_connections() {
            return {
                connections[DirectionIndex::TOP] != nullptr,
                connections[DirectionIndex::BOTTOM] != nullptr,
                connections[DirectionIndex::LEFT] != nullptr,
                connections[DirectionIndex::RIGHT] != nullptr,
            };
        }
    };

   public:
    Dungeon(Handle<Player> player) : _player(player) { this->_rooms = std::make_unique<RoomVector>(); }

    ~Dungeon() = default;

    // TODO: Change player position
    void change_room(Room *room, const Vector2Df &new_position) {
        this->_current_room->set_active(false);
        this->_current_room = room;
        this->_player->get_transform_component()->set_position(new_position);
        this->_current_room->set_active(true);
    }

    // OPTIMIZE: This isn't so fast
    void generate(unsigned int room_count) {
        const unsigned int max_room_index = 11;

        std::random_device random_device;
        std::mt19937 generator(time(NULL));

        std::bernoulli_distribution door_distribution;  // For bools
        std::uniform_int_distribution<unsigned int> room_position_distribution(0, room_count - 1);
        std::uniform_int_distribution<unsigned int> room_distribution(0, max_room_index);

        // TODO: Rename to node
        std::queue<DoorMap *> unprocessed_door_maps;
        std::vector<DoorMap *> processed_door_maps;

        DoorMap *initial_node = new DoorMap();
        initial_node->remaining_rooms = room_count;

        unprocessed_door_maps.push(initial_node);

        do {
            DoorMap *node = unprocessed_door_maps.front();
            unprocessed_door_maps.pop();

            node->remaining_rooms--;

            if (node->remaining_rooms == 0) {
                processed_door_maps.push_back(node);

                continue;
            }

            Direction chosen_directions;
            unsigned int directions = 0;

            while (directions == 0 || directions > node->remaining_rooms) {
                chosen_directions = random_directions(generator) & node->available_directions;
                directions = direction_count(chosen_directions);
            }

            unsigned int remaining_rooms_per_direction = node->remaining_rooms / directions;
            int remainder = static_cast<int>(node->remaining_rooms % directions);

            if ((chosen_directions & Direction::TOP) != Direction::NONE) {
                DoorMap *top_node = new DoorMap();

                node->connections[DirectionIndex::TOP] = top_node;
                top_node->connections[DirectionIndex::BOTTOM] = node;

                node->available_directions &= ~Direction::TOP;
                top_node->available_directions &= ~Direction::BOTTOM;

                top_node->remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= top_node->remaining_rooms;

                unprocessed_door_maps.push(top_node);
            }

            if ((chosen_directions & Direction::BOTTOM) != Direction::NONE) {
                DoorMap *bottom_node = new DoorMap();

                node->connections[DirectionIndex::BOTTOM] = bottom_node;
                bottom_node->connections[DirectionIndex::TOP] = node;

                node->available_directions &= ~Direction::BOTTOM;
                bottom_node->available_directions &= ~Direction::TOP;

                bottom_node->remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= bottom_node->remaining_rooms;

                unprocessed_door_maps.push(bottom_node);
            }

            if ((chosen_directions & Direction::LEFT) != Direction::NONE) {
                DoorMap *left_node = new DoorMap();

                node->connections[DirectionIndex::LEFT] = left_node;
                left_node->connections[DirectionIndex::RIGHT] = node;

                node->available_directions &= ~Direction::LEFT;
                left_node->available_directions &= ~Direction::RIGHT;

                left_node->remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= left_node->remaining_rooms;

                unprocessed_door_maps.push(left_node);
            }

            if ((chosen_directions & Direction::RIGHT) != Direction::NONE) {
                DoorMap *right_node = new DoorMap();

                node->connections[DirectionIndex::RIGHT] = right_node;
                right_node->connections[DirectionIndex::LEFT] = node;

                node->available_directions &= ~Direction::RIGHT;
                right_node->available_directions &= ~Direction::LEFT;

                right_node->remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= right_node->remaining_rooms;

                unprocessed_door_maps.push(right_node);
            }

            processed_door_maps.push_back(node);
        } while (!unprocessed_door_maps.empty());

        for (auto node : processed_door_maps) {
            unsigned int index = room_distribution(generator);

            this->_rooms->push_back(std::make_unique<Room>(
                std::format("assets/rooms/room_{}.room", index), node->valid_connections(), this, this->_player));
            node->room = this->_rooms->back().get();
        }

        for (unsigned int i = 0; i < processed_door_maps.size(); i++) {
            DoorMap *door_map = processed_door_maps[i];

            for (unsigned int j = 0; j < 4; j++) {
                DoorMap *connection = door_map->connections[j];

                if (connection != nullptr) {
                    (*this->_rooms)[i]->connect_to_room(connection->room, static_cast<DirectionIndex>(j));
                }
            }

            delete processed_door_maps[i];
        }

        this->_current_room = (*this->_rooms.get())[0].get();
        this->_current_room->set_active(true);
        this->_player->get_transform_component()->set_position(this->_current_room->player_spawn());
    }

   private:
    std::unique_ptr<RoomVector> _rooms;
    Room *_current_room;
    Handle<Player> _player;
};
