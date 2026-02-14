#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

class PlayerComponent : public BehaviorComponent {
   public:
    PlayerComponent(Entity *entity);

    PlayerComponent(PlayerComponent &&other) : BehaviorComponent(std::move(other)) { this->_move(std::move(other)); }

    ~PlayerComponent() override {}

    PlayerComponent &operator=(PlayerComponent &&other) {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline void start() override {}

    void update() override;

   private:
    void _move(PlayerComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_physics_component = std::move(other._physics_component);
    }

   private:
    utils::Handle<PhysicsComponent> _physics_component;
};
