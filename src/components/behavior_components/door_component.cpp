#include "components/behavior_components/door_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "entities/entity.hpp"

DoorComponent::DoorComponent(Handle<Entity> entity, const DoorComponentArgs &args)
    : BehaviorComponent(entity),
      _target_room(args.target_room),
      _exit_position(args.exit_position) {
    log_trace(this, __PRETTY_FUNCTION__, entity);
}

void DoorComponent::_move(DoorComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_target_room = std::move(other._target_room);
    this->_exit_position = std::move(other._exit_position);
}
