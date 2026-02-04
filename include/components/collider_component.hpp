#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "raylib.h"

struct ColliderComponentArgs {
    Rectangle rectangle = Rectangle();
};

// For now this is only a rect collider
class ColliderComponent final : public Component {
   public:
    ColliderComponent(GameCore *game_core, Entity *entity, const ColliderComponentArgs &args = ColliderComponentArgs());

    ~ColliderComponent() override = default;

   private:
    void _update_rectangle();

   private:
    Rectangle _rectangle;
    TransformComponent *_transform_component;
    TransformComponent::TransformUpdateListener _transform_update_listener;
};
