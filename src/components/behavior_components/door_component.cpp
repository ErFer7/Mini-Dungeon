#include "components/behavior_components/door_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "entities/entity.hpp"
#include "gameplay/dungeon.hpp"

DoorComponent::DoorComponent(Handle<Entity> entity, const DoorComponentArgs &args)
    : BehaviorComponent(entity),
      _target_room(args.target_room),
      _exit_position(args.exit_position) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    _dungeon = args.dungeon;

    _on_collision_listener.bind_callable<DoorComponent, &DoorComponent::_handle_pass>(
        this->make_handle<DoorComponent>());
    _on_collision_listener.subscribe(this->get_entity()->get_component<ColliderComponent>()->get_collision_event());
}

void DoorComponent::_move(DoorComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_target_room = std::move(other._target_room);
    this->_dungeon = std::move(other._dungeon);
    this->_exit_position = std::move(other._exit_position);
    this->_on_collision_listener = std::move(other._on_collision_listener);
}

void DoorComponent::_handle_pass(Handle<ColliderComponent> &) {
    log_trace(this, __PRETTY_FUNCTION__);

    this->_dungeon->change_room(this->_target_room, this->_exit_position);
}
