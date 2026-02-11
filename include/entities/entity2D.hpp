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
    float texture_scale = 1.0f;

    operator TransformComponentArgs() const { return TransformComponentArgs{position, rotation, scale}; }

    operator GraphicsComponentArgs() const {
        return GraphicsComponentArgs{texture, rendering_mode, color, layer, texture_scale};
    }
};

class Entity2D : public Entity {
   public:
    Entity2D(const Entity2DArgs &args);

    ~Entity2D() override = default;

    inline utils::Handle<TransformComponent> get_transform_component() { return this->_transform_component; }

    inline utils::Handle<GraphicsComponent> get_graphics_component() { return this->_graphics_component; }

   private:
    utils::Handle<TransformComponent> _transform_component;
    utils::Handle<GraphicsComponent> _graphics_component;
};
