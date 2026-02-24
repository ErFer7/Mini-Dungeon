#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;

class PlayerComponent : public BehaviorComponent {
   public:
    PlayerComponent(Handle<Entity> entity);

    PlayerComponent(PlayerComponent &&other) noexcept : BehaviorComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~PlayerComponent() override {}

    inline PlayerComponent &operator=(PlayerComponent &&other) noexcept {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    void update() override;

   private:
    void _move(PlayerComponent &&other);

   private:
    Handle<PhysicsComponent> _physics_component;
};
