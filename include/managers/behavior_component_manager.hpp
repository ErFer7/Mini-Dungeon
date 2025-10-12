#pragma once

#include "managers/component_manager.hpp"

class BehaviorComponentManager : public ComponentManager {
    friend class BehaviorComponent;

   public:
    BehaviorComponentManager() = default;

    BehaviorComponentManager(GameCore *game_core) : ComponentManager(game_core){};

    ~BehaviorComponentManager() override = default;

    void init() override;
    void update() override;
    void exit() override;
};
