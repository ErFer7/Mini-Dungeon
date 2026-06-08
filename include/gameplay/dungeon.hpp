#pragma once

#include <memory>
#include <queue>
#include <random>
#include <vector>

#include "entities/entity2D.hpp"
#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/direction.hpp"
#include "utils/vector.hpp"

using utils::Direction;
using utils::direction_count;
using utils::Handle;
using utils::log_info;
using utils::log_warn;
using utils::random_directions;
using utils::Vector2Df;
using utils::Vector2Di;

class Dungeon {
   private:
    struct DoorMap {
        DoorMap *connections[4];  // Top, Bottom, Left, Right
        unsigned int remaining_rooms;

        DoorMap() : remaining_rooms(0) {}
    };

   public:
    class Room {
       public:
        typedef std::vector<Handle<Entity2D>> TileVector;

       private:
        enum TileType { FLOOR, OBSTACLE, BACKGROUND, DOOR };

       public:
        Room(std::string room_path, DoorMap *door_map);

        Room() = default;

        ~Room() = default;

        void connect_to_room(Room *other);

        void set_active(bool ative);

       private:
        void _create_tile(std::string sprite_path,
                          Vector2Df position,
                          TileType tile_type,
                          Direction tile_collider_direction = Direction::CENTER);

       private:
        std::unique_ptr<TileVector> _tiles;
    };

    typedef std::vector<std::unique_ptr<Room>> RoomVector;

   public:
    Dungeon() { this->_rooms = std::make_unique<RoomVector>(); }

    ~Dungeon() = default;

    // TODO: Change player position
    void change_room(Room *room) {
        this->_current_room->set_active(false);
        this->_current_room = room;
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

        DoorMap initial_node = DoorMap();
        initial_node.remaining_rooms = room_count;

        unprocessed_door_maps.push(&initial_node);

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
                chosen_directions = random_directions(generator);
                directions = direction_count(chosen_directions);
            }

            unsigned int remaining_rooms_per_direction = node->remaining_rooms / directions;
            unsigned int remainder = node->remaining_rooms % directions;

            if ((chosen_directions & Direction::TOP) != Direction::NONE) {
                DoorMap top_node = DoorMap();

                node->connections[0] = &top_node;
                top_node.connections[1] = node;
                top_node.remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= top_node.remaining_rooms;

                unprocessed_door_maps.push(&top_node);
            }

            if ((chosen_directions & Direction::BOTTOM) != Direction::NONE) {
                DoorMap bottom_node = DoorMap();

                node->connections[1] = &bottom_node;
                bottom_node.connections[0] = node;
                bottom_node.remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= bottom_node.remaining_rooms;

                unprocessed_door_maps.push(&bottom_node);
            }

            if ((chosen_directions & Direction::LEFT) != Direction::NONE) {
                DoorMap left_node = DoorMap();

                node->connections[2] = &left_node;
                left_node.connections[3] = node;
                left_node.remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= left_node.remaining_rooms;

                unprocessed_door_maps.push(&left_node);
            }

            if ((chosen_directions & Direction::RIGHT) != Direction::NONE) {
                DoorMap right_node = DoorMap();

                node->connections[3] = &right_node;
                right_node.connections[2] = node;
                right_node.remaining_rooms = remaining_rooms_per_direction + (remainder-- > 0 ? 1 : 0);
                node->remaining_rooms -= right_node.remaining_rooms;

                unprocessed_door_maps.push(&right_node);
            }

            processed_door_maps.push_back(node);
        } while (!unprocessed_door_maps.empty());

        Room *rooms[room_count][room_count];

        for (auto node : processed_door_maps) {
            unsigned int index = room_distribution(generator);

            this->_rooms->push_back(std::make_unique<Room>(std::format("assets/rooms/room_{}.room", index), node));
        }

        this->_current_room = (*this->_rooms.get())[0].get();
        this->_current_room->set_active(true);
    }

   private:
    std::unique_ptr<RoomVector> _rooms;
    Room *_current_room;
};
