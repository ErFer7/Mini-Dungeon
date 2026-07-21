#pragma once

#include "components/behavior_components/player_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct PlayerArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    int max_health;
    int initial_health = -1;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    Vector2Df initial_velocity = Vector2Df();
    Vector2Df initial_acceleration = Vector2Df();
    float drag = 5.0f;
    bool is_collider_trigger = false;
    Rectangle collider_rectangle = Rectangle();
    float texture_scale = VIRTUAL_SCALE;

    operator DynamicPhysicalEntity2DArgs() const {
        return DynamicPhysicalEntity2DArgs{texture,
                                           rendering_mode,
                                           position,
                                           rotation,
                                           scale,
                                           color,
                                           layer,
                                           initial_velocity,
                                           initial_acceleration,
                                           drag,
                                           is_collider_trigger,
                                           collider_rectangle,
                                           texture_scale};
    }

    operator PlayerComponentArgs() const { return PlayerComponentArgs{max_health, initial_health}; }
};

class Player final : public DynamicPhysicalEntity2D {
   public:
    Player(const PlayerArgs &args);

    ~Player() override = default;

    inline Handle<PlayerComponent> get_player_component() { return this->_player_component; }

    inline Handle<WalkingAnimationComponent> get_walking_animation_component() {
        return this->_walking_animation_component;
    }

   private:
    Handle<PlayerComponent> _player_component;
    Handle<WalkingAnimationComponent> _walking_animation_component;
};
