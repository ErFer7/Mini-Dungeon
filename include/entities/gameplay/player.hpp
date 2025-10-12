#pragma once

#include "components/behavior_components/player_component.hpp"
#include "entities/physical_entity2D.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

class Player : public PhysicalEntity2D {
   public:
    Player(GameCore *game_core, const PhysicalEntity2DArgs &args);

    ~Player() override = default;

    inline PlayerComponent *get_player_component() { return this->_player_component; }

   private:
    PlayerComponent *_player_component;
};
