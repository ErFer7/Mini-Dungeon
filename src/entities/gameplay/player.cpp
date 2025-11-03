#include "entities/gameplay/player.hpp"

#include "components/behavior_components/player_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"

Player::Player(GameCore *game_core, const DynamicPhysicalEntity2DArgs &args)
    : DynamicPhysicalEntity2D(game_core, args) {
    this->_player_component = this->create_component<PlayerComponent>();
}