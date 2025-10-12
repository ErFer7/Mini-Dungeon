#include "entities/gameplay/player.hpp"

#include "components/behavior_components/player_component.hpp"
#include "entities/physical_entity2D.hpp"

Player::Player(GameCore *game_core, const PhysicalEntity2DArgs &args) : PhysicalEntity2D(game_core, args) {
    this->_player_component = this->create_component<PlayerComponent>();
}