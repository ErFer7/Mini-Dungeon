#pragma once

#include "../components/graphics_component.hpp"
#include "../types.hpp"
#include "entity.hpp"

class Entity2D : public Entity {
   public:
    Entity2D(GameCore *game_core,
             Texture2D texture,
             RenderingMode rendering_mode,
             Vector2 position = Vector2Zero(),
             float rotation = 0.0f,
             Vector2 scale = Vector2One(),
             Color color = WHITE,
             int layer = 0);

    ~Entity2D() override = default;

    inline TransformComponent *get_transform_component() { return this->_transform_component; }

    inline GraphicsComponent *get_graphics_component() { return this->_graphics_component; }

   private:
    TransformComponent *_transform_component;
    GraphicsComponent *_graphics_component;
};
