#pragma once

#include <memory>
#include <queue>
#include <random>
#include <vector>

#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::log_info;
using utils::log_warn;
using utils::Vector2Df;
using utils::Vector2Di;

class Dungeon {
   private:
    struct DoorMap {
        bool processed;
        bool top;
        bool bottom;
        bool left;
        bool right;
    };

   public:
    class Room {
       public:
        typedef std::vector<Handle<Entity2D>> TileVector;

       private:
        // TODO: Define something more generic with this
        enum TileColliderDirection {
            NONE,
            TOP_LEFT,
            TOP,
            TOP_RIGHT,
            LEFT,
            CENTER,
            RIGHT,
            BOTTOM_LEFT,
            BOTTOM,
            BOTTOM_RIGHT
        };

        enum TileType { FLOOR, OBSTACLE, BACKGROUND, DOOR };

       public:
        Room(std::string room_path, DoorMap door_map);

        ~Room() = default;

        void connect_to_room(Room *other);

        void set_active(bool ative);

       private:
        void _create_tile(std::string sprite_path,
                          Vector2Df position,
                          TileType tile_type,
                          TileColliderDirection tile_collider_direction = NONE);

       private:
        std::unique_ptr<TileVector> _tiles;
    };

    typedef std::vector<std::unique_ptr<Room>> RoomVector;

   public:
    Dungeon() { this->_rooms = std::make_unique<RoomVector>(); }

    ~Dungeon() = default;

    // OPTIMIZE: This isn't so fast
    void generate(unsigned int room_count) {
        const unsigned int max_room_index = 11;

        std::random_device random_device;
        std::mt19937 generator(time(NULL));

        std::bernoulli_distribution door_distribution;  // For bools
        std::uniform_int_distribution<unsigned int> room_position_distribution(0, room_count - 1);
        std::uniform_int_distribution<unsigned int> room_distribution(0, max_room_index);

        DoorMap door_maps[room_count][room_count];

        for (unsigned int i = 0; i < room_count; i++) {
            for (unsigned int j = 0; j < room_count; j++) {
                door_maps[i][j].processed = false;
                door_maps[i][j].top = false;
                door_maps[i][j].bottom = false;
                door_maps[i][j].right = false;
                door_maps[i][j].left = false;
            }
        }

        std::queue<Vector2Di> unprocessed_door_maps;
        std::vector<Vector2Di> processed_door_maps;

        unprocessed_door_maps.push(
            Vector2Di(room_position_distribution(generator), room_position_distribution(generator)));

        unsigned int remaining_door_maps = room_count;

        // FIX: This can still fail. For some reason the queue is consumed before all door maps are generated
        // FIX: It's possible to generate doors to nowhere
        do {
            Vector2Di position = unprocessed_door_maps.front();
            unprocessed_door_maps.pop();
            DoorMap *door_map = &door_maps[position.y][position.x];

            if (room_count > 1) {
                unsigned int tries = 0;

                do {
                    if (position.y > 0 && !door_maps[position.y - 1][position.x].processed) {
                        door_map->top = door_distribution(generator);
                    }

                    if (position.y < room_count - 1 && !door_maps[position.y + 1][position.x].processed) {
                        door_map->bottom = door_distribution(generator);
                    }

                    if (position.x > 0 && !door_maps[position.y][position.x - 1].processed) {
                        door_map->left = door_distribution(generator);
                    }

                    if (position.x < room_count - 1 && !door_maps[position.y][position.x + 1].processed) {
                        door_map->right = door_distribution(generator);
                    }

                    tries++;
                } while (!(door_map->top || door_map->bottom || door_map->left || door_map->right));

                if (tries > 10) {
                    log_warn(this, "Dungeon: it took ", tries, " tries to generate a door map!");
                }
            }

            door_map->processed = true;
            remaining_door_maps--;
            processed_door_maps.push_back(position);

            if (door_map->top && !door_maps[position.y - 1][position.x].processed) {
                door_maps[position.y - 1][position.x].bottom = true;
                unprocessed_door_maps.push(Vector2Di(position.y - 1, position.x));
            }

            if (door_map->bottom && !door_maps[position.y + 1][position.x].processed) {
                door_maps[position.y + 1][position.x].top = true;
                unprocessed_door_maps.push(Vector2Di(position.y + 1, position.x));
            }

            if (door_map->left && !door_maps[position.y][position.x - 1].processed) {
                door_maps[position.y][position.x - 1].right = true;
                unprocessed_door_maps.push(Vector2Di(position.y, position.x - 1));
            }

            if (door_map->right && !door_maps[position.y][position.x + 1].processed) {
                door_maps[position.y][position.x + 1].left = true;
                unprocessed_door_maps.push(Vector2Di(position.y, position.x + 1));
            }
        } while (remaining_door_maps > 0);

        Room *rooms[room_count][room_count];

        for (auto position : processed_door_maps) {
            unsigned int index = room_distribution(generator);

            this->_rooms->push_back(std::make_unique<Room>(std::format("assets/rooms/room_{}.room", index),
                                                           door_maps[position.y][position.x]));

            rooms[position.y][position.x] = this->_rooms->back().get();
        }

        this->_current_room = (*this->_rooms.get())[0].get();
        this->_current_room->set_active(true);
    }

   private:
    std::unique_ptr<RoomVector> _rooms;
    Room *_current_room;
};
