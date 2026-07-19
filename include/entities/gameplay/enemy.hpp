#pragma once

#include "components/behavior_components/enemy_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct EnemyArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Handle<Player> player;
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

    operator EnemyComponentArgs() const { return EnemyComponentArgs{player}; }
};

class Enemy final : public DynamicPhysicalEntity2D {
   public:
    Enemy(const EnemyArgs &args);

    ~Enemy() override = default;

    inline Handle<EnemyComponent> get_enemy_component() { return this->_enemy_component; }

    inline Handle<WalkingAnimationComponent> get_walking_animation_component() {
        return this->_walking_animation_component;
    }

   private:
    Handle<EnemyComponent> _enemy_component;
    Handle<WalkingAnimationComponent> _walking_animation_component;
};
