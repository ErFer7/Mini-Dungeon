#pragma once

#include "../types.hpp"
#include "../components/graphics_component.hpp"
#include "entity.hpp"

class Entity2D : public Entity {
   public:
    Entity2D(GameCore *game_core, RenderingMode rendering_mode);

    ~Entity2D() override = default;

    inline TransformComponent *get_transform_component() { return this->_transform_component; }

    inline GraphicsComponent *get_graphics_component() { return this->_graphics_component; }

   private:
    TransformComponent *_transform_component;
    GraphicsComponent *_graphics_component;
};
