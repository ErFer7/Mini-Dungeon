#pragma once

#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"
#include "entities/entity2D.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "managers/graphics_component_manager.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct DynamicPhysicalEntity2DArgs {
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
    Rectangle collider_rectangle = Rectangle();
    float texture_scale = VIRTUAL_SCALE;

    operator StaticPhysicalEntity2DArgs() const {
        return StaticPhysicalEntity2DArgs{
            texture, rendering_mode, position, rotation, scale, color, layer, texture_scale, collider_rectangle};
    }

    operator PhysicsComponentArgs() const { return PhysicsComponentArgs{initial_velocity, initial_acceleration, drag}; }
};

class DynamicPhysicalEntity2D : public StaticPhysicalEntity2D {
   public:
    DynamicPhysicalEntity2D(const DynamicPhysicalEntity2DArgs &args);

    ~DynamicPhysicalEntity2D() override = default;

    inline utils::Handle<PhysicsComponent> get_physics_component() { return this->_physics_component; }

   private:
    utils::Handle<PhysicsComponent> _physics_component;
};
