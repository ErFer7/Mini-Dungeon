#include "entities/gameplay/player.hpp"

#include "components/behavior_components/player_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "containers/entity_container.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "entities/gameplay/sword.hpp"

Player::Player(const PlayerArgs &args) : DynamicPhysicalEntity2D(args), _sword(args.sword) {
    this->_walking_animation_component = this->create_component<WalkingAnimationComponent>();
    this->_player_component = this->create_component<PlayerComponent>(args);

    this->_sword->get_activity_state()->set_parent_activity_state(this->get_activity_state());
}
