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

    ColliderComponent(ColliderComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~ColliderComponent() override = default;

    ColliderComponent &operator=(ColliderComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

   private:
    void _move(ColliderComponent &&other) {
        if (this != &other) {  // TODO: Invert these checks
            this->_rectangle = std::move(other._rectangle);
            this->_transform_component = std::move(other._transform_component);
            this->_transform_update_listener = std::move(other._transform_update_listener);
        }
    }

    void _update_rectangle();

    void _update_rectangle_listener_call(const Vector2Df &, const TransformData &) { this->_update_rectangle(); }

   private:
    Rectangle _rectangle;
    utils::Handle<TransformComponent> _transform_component;
    TransformComponent::TransformUpdateListener _transform_update_listener;
};
