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
};

class DoorComponent : public BehaviorComponent {
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

   private:
    void _move(DoorComponent &&other);

   private:
    Room *_target_room;
    Vector2Df _exit_position;
};
