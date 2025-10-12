#pragma once

#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"
#include "entities/entity2D.hpp"
#include "managers/graphics_component_manager.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct PhysicalEntity2DArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    Vector2Df initial_velocity = Vector2Df();
    Vector2Df initial_acceleration = Vector2Df();
    float drag = 5.0f;
    float texture_scale = VIRTUAL_SCALE;

    operator Entity2DArgs() const {
        return Entity2DArgs{texture, rendering_mode, position, rotation, scale, color, layer, texture_scale};
    }

    operator PhysicsComponentArgs() const { return PhysicsComponentArgs{initial_velocity, initial_acceleration, drag}; }
};

class PhysicalEntity2D : public Entity2D {
   public:
    PhysicalEntity2D(GameCore *game_core, const PhysicalEntity2DArgs &args);

    ~PhysicalEntity2D() override = default;

    inline PhysicsComponent *get_physics_component() { return this->_physics_component; }

   private:
    PhysicsComponent *_physics_component;
};
