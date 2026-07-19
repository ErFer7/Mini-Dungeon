#pragma once

#include "components/behavior_components/animation_component.hpp"
#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;
using utils::log_warn;

class WalkingAnimationComponent : public AnimationComponent {
   public:
    enum PlayerAnimation { IDLE, FLIP_LEFT, FLIP_RIGHT };

    WalkingAnimationComponent(Handle<Entity> entity);

    WalkingAnimationComponent(WalkingAnimationComponent &&other) noexcept : AnimationComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~WalkingAnimationComponent() override = default;

    inline WalkingAnimationComponent &operator=(WalkingAnimationComponent &&other) noexcept {
        AnimationComponent::operator=(std::move(other));
        this->_move(std::move(other));
        return *this;
    }

   private:
    void _move(WalkingAnimationComponent &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->_physics_component = std::move(other._physics_component);
    }

    // TODO: Simplify this
    void _flip_left() {
        if (!this->graphics_component()->is_flipped_horizontally()) {
            this->graphics_component()->flip_horizontally();
        }
    }

    void _flip_right() {
        if (this->graphics_component()->is_flipped_horizontally()) {
            this->graphics_component()->flip_horizontally();
        }
    }

    void _run() {
        if (!this->_physics_component->get_velocity().is_approximately_zero()) {
            this->graphics_component()->set_offset(Vector2Df(
                0.0f,
                std::abs(std::sin(GetTime() * 25.0f) * this->_physics_component->get_velocity().magnitude() * 0.05f)));
        }
    }

   private:
    Handle<PhysicsComponent> _physics_component;
};
