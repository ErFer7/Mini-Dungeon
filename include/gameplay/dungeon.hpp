#pragma once

#include <memory>
#include <vector>

#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::log_warn;
using utils::Vector2Df;

class Dungeon {
   private:
    class Room {
       public:
        typedef std::vector<Handle<Entity2D>> TileVector;

       public:
        Room(std::string room_path, bool top_door, bool bottom_door, bool left_door, bool right_door);

        ~Room() = default;

       private:
        void _create_wall(std::string sprite_path, Vector2Df position, float rotation = 0.0f);

        void _create_floor(std::string sprite_path, Vector2Df position, float rotation = 0.0f);

       private:
        std::unique_ptr<TileVector> _tiles;
    };

    typedef std::vector<std::unique_ptr<Room>> RoomVector;

   public:
    Dungeon() { this->_rooms = std::make_unique<RoomVector>(); }

    ~Dungeon() = default;

    void generate() {
        this->_rooms->push_back(std::make_unique<Room>("assets/rooms/room_0.room", false, false, false, false));
    }

   private:
    std::unique_ptr<RoomVector> _rooms;
};
