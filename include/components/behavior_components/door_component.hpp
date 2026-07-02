#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct DoorComponentArgs {
    Room *target_room = nullptr;
    Vector2Df exit_position = Vector2Df();
    Dungeon *dungeon = nullptr;
};

class DoorComponent : public BehaviorComponent {
   private:
    typedef ColliderComponent::CollisionListener CollisionListener;

   public:
    DoorComponent(Handle<Entity> entity, const DoorComponentArgs &args = DoorComponentArgs());

    DoorComponent(DoorComponent &&other) noexcept : BehaviorComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~DoorComponent() override {}

    inline DoorComponent &operator=(DoorComponent &&other) noexcept {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    void update() override {}

    inline void set_exit(Room *target_room, const Vector2Df &exit_position) {
        this->_target_room = target_room;
        this->_exit_position = exit_position;
    }

   private:
    void _move(DoorComponent &&other);

    void _handle_pass(Handle<ColliderComponent> &);

   private:
    Room *_target_room;
    Dungeon *_dungeon;
    Vector2Df _exit_position;
    CollisionListener _on_collision_listener;
};
