#pragma once

#include "components/graphics_component.hpp"
#include "entity.hpp"
#include "managers/graphics_component_manager.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct Entity2DArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;

    operator TransformComponentArgs() const { return TransformComponentArgs{position, rotation, scale}; }

    operator GraphicsComponentArgs() const { return GraphicsComponentArgs{texture, rendering_mode, color, layer}; }
};

class Entity2D : public Entity {
   public:
    Entity2D(GameCore *game_core, const Entity2DArgs &args);

    ~Entity2D() override = default;

    inline TransformComponent *get_transform_component() { return this->_transform_component; }

    inline GraphicsComponent *get_graphics_component() { return this->_graphics_component; }

   private:
    TransformComponent *_transform_component;
    GraphicsComponent *_graphics_component;
};
