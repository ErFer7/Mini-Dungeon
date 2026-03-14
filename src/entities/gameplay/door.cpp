#include "entities/gameplay/door.hpp"

#include "components/behavior_components/door_component.hpp"
#include "components/behavior_components/player_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "entities/static_physical_entity2D.hpp"

Door::Door(const DoorArgs &args) : StaticPhysicalEntity2D(args) {
    this->_door_component = this->create_component<DoorComponent>(DoorComponentArgs{args.target_room, args.exit_position});
}
