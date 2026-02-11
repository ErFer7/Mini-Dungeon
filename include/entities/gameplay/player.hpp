#pragma once

#include "entities/dynamic_physical_entity2D.hpp"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

class Player : public DynamicPhysicalEntity2D {
   public:
    Player(const DynamicPhysicalEntity2DArgs &args);

    ~Player() override = default;

    inline utils::Handle<PlayerComponent> get_player_component() { return this->_player_component; }

   private:
    utils::Handle<PlayerComponent> _player_component;
};
