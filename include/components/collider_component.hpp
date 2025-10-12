#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct ColliderComponentArgs {
    Rectangle rectangle = Rectangle();
};

// For now this is only a rect collider
class ColliderComponent : public Component {
   public:
    ColliderComponent(GameCore *game_core, Entity *entity, const ColliderComponentArgs &args = ColliderComponentArgs());

    ~ColliderComponent() override = default;

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    Rectangle _rectangle;
    TransformComponent *_transform_component;
};
