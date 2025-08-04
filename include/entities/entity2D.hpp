#pragma once

#include "../types.hpp"
#include "entity.hpp"

class Entity2D : public Entity {
   public:
    Entity2D(EngineCore *engine_core, Entity *parent);

    ~Entity2D() override = default;

    inline Transform2DComponent *get_transform_component() { return this->_transform_component; }

    inline Graphics2DComponent *get_graphics_component() { return this->_graphics_component; }

   private:
    Transform2DComponent *_transform_component;
    Graphics2DComponent *_graphics_component;
};