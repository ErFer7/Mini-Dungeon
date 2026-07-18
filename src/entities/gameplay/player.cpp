#include "entities/gameplay/player.hpp"

#include "components/behavior_components/player_animation_component.hpp"
#include "components/behavior_components/player_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"

Player::Player(const DynamicPhysicalEntity2DArgs &args) : DynamicPhysicalEntity2D(args) {
    this->_player_animation_component = this->create_component<PlayerAnimationComponent>();
    this->_player_component = this->create_component<PlayerComponent>();
}
