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
    ColliderComponent(Entity *entity, const ColliderComponentArgs &args = ColliderComponentArgs());

    ColliderComponent(ColliderComponent &&other) noexcept = default;

    ~ColliderComponent() override = default;

    ColliderComponent &operator=(ColliderComponent &&other) noexcept = default;

   private:
    void _update_rectangle();

   private:
    Rectangle _rectangle;
    utils::Handle<TransformComponent> _transform_component;
    TransformComponent::TransformUpdateListener _transform_update_listener;
};
