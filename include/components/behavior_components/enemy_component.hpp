#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;

struct EnemyComponentArgs {
    Handle<Player> player;
};

class EnemyComponent : public BehaviorComponent {
   public:
    EnemyComponent(Handle<Entity> entity, const EnemyComponentArgs &args = EnemyComponentArgs());

    EnemyComponent(EnemyComponent &&other) noexcept : BehaviorComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~EnemyComponent() override {}

    inline EnemyComponent &operator=(EnemyComponent &&other) noexcept {
        EnemyComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    void update() override;

   private:
    void _move(EnemyComponent &&other);

   private:
    Handle<TransformComponent> _transform_component;
    Handle<PhysicsComponent> _physics_component;
    Handle<WalkingAnimationComponent> _walking_animation_component;
    Handle<Player> _player;
};
