#pragma once

#include "components/behavior_components/player_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

class Player : public DynamicPhysicalEntity2D {
   public:
    Player(GameCore *game_core, const DynamicPhysicalEntity2DArgs &args);

    ~Player() override = default;

    inline PlayerComponent *get_player_component() { return this->_player_component; }

   private:
    PlayerComponent *_player_component;
};
