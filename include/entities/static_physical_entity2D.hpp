#pragma once

#include "components/collider_component.hpp"
#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "definitions.hpp"
#include "entities/entity2D.hpp"
#include "managers/graphics/graphics_manager.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct StaticPhysicalEntity2DArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    float texture_scale = VIRTUAL_SCALE;
    Rectangle collider_rectangle = Rectangle();

    operator Entity2DArgs() const {
        return Entity2DArgs{texture, rendering_mode, position, rotation, scale, color, layer, texture_scale};
    }

    operator ColliderComponentArgs() const { return ColliderComponentArgs{collider_rectangle}; }
};

class StaticPhysicalEntity2D : public Entity2D {
   public:
    StaticPhysicalEntity2D(const StaticPhysicalEntity2DArgs &args);

    ~StaticPhysicalEntity2D() override = default;

    inline Handle<ColliderComponent> get_collider_component() { return this->_collider_component; }

   private:
    Handle<ColliderComponent> _collider_component;
};
