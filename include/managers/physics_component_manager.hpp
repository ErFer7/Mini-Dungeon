#pragma once

#include <vector>

#include "components/physics_component.hpp"
#include "containers/component_containers/stack_allocated_component_container.hpp"
#include "managers/manager.hpp"

using std::vector;

class PhysicsComponentManager : public Manager {
    friend class PhysicsComponent;

   public:
    PhysicsComponentManager() = default;

    PhysicsComponentManager(GameCore *game_core) : Manager(game_core){};

    ~PhysicsComponentManager() override = default;

    void init() override {};
    void update() override;
    void exit() override {};

   private:
    PhysicsComponentContainer *_physics_component_container;
};
