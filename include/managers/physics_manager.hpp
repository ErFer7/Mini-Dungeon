#pragma once

#include <vector>

#include "components/physics_component.hpp"
#include "managers/manager.hpp"

using std::vector;

class PhysicsManager final : public Manager {
    friend class PhysicsComponent;

   public:
    PhysicsManager() = default;

    ~PhysicsManager() override = default;

    void init() override;
    void update() override;
    void exit() override {};

   private:
    PhysicsComponentContainer *_physics_component_container;
    ColliderComponentContainer *_collider_component_container;
};
