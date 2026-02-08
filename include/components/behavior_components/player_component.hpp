#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "entities/entity.hpp"

class PlayerComponent : public BehaviorComponent {
   public:
    PlayerComponent(Entity *entity);

    ~PlayerComponent() override {}

    inline void start() override {}

    void update() override;

   private:
    PhysicsComponent *_physics_component;
};
