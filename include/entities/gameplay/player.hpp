#pragma once

#include "components/behavior_components/walking_animation_component.hpp"
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

    inline Handle<WalkingAnimationComponent> get_walking_animation_component() {
        return this->_walking_animation_component;
    }

   private:
    Handle<PlayerComponent> _player_component;
    Handle<WalkingAnimationComponent> _walking_animation_component;
};
