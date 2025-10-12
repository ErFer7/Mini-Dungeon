#pragma once

#include "managers/component_manager.hpp"

class PhysicsComponentManager : public ComponentManager {
    friend class PhysicsComponent;

   public:
    PhysicsComponentManager() = default;

    PhysicsComponentManager(GameCore *game_core) : ComponentManager(game_core){};

    ~PhysicsComponentManager() override = default;

    void init() override {};
    void update() override;
    void exit() override {};
};
