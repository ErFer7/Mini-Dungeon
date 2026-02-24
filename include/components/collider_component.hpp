#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "raylib.h"
#include "utils/debug.hpp"

using utils::Handle;
using utils::log_info;

struct ColliderComponentArgs {
    Rectangle rectangle = Rectangle();
};

// For now this is only a rect collider
class ColliderComponent final : public Component {
    friend class PhysicsManager;

   public:
    ColliderComponent(Handle<Entity> entity, const ColliderComponentArgs &args = ColliderComponentArgs());

    ColliderComponent(ColliderComponent &&other) noexcept : Component(std::move(other)) {
        this->_move(std::move(other));
    }

    ~ColliderComponent() override = default;

    inline ColliderComponent &operator=(ColliderComponent &&other) noexcept {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    // TODO: Possibly make this private to avoid misuse
    // TODO: Solve the problem of N:1 colliders to physics components
    inline void set_physics_component(Handle<PhysicsComponent> physics_component) {
        this->_physics_component = physics_component;
    }

    bool check_collision(Handle<ColliderComponent> &other);

    void debug_draw() override;

   private:
    void _move(ColliderComponent &&other);

    void _update_rectangle();

    void _update_rectangle_listener_call(const Vector2Df &, const TransformData &) { this->_update_rectangle(); }

    inline Handle<PhysicsComponent> _get_physics_component() { return this->_physics_component; }

    inline Handle<TransformComponent> _get_transform_component() { return this->_transform_component; }

   private:
    Rectangle _rectangle;
    Vector2Df _offset;
    Handle<TransformComponent> _transform_component;
    Handle<PhysicsComponent> _physics_component;
    TransformComponent::TransformUpdateListener _transform_update_listener;
};
