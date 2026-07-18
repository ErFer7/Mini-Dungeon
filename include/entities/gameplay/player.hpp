#pragma once

#include "components/behavior_components/player_animation_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

class Player final : public DynamicPhysicalEntity2D {
   public:
    Player(const DynamicPhysicalEntity2DArgs &args);

    ~Player() override = default;

    inline Handle<PlayerComponent> get_player_component() { return this->_player_component; }

    inline Handle<PlayerAnimationComponent> get_player_animation_component() {
        return this->_player_animation_component;
    }

   private:
    Handle<PlayerComponent> _player_component;
    Handle<PlayerAnimationComponent> _player_animation_component;
};
