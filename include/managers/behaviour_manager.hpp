#pragma once

#include "../types.hpp"
#include "component_manager.hpp"

class BehaviourManager : public ComponentManager {
    friend class BehaviourComponent;

   public:
    BehaviourManager(EngineCore *engine_core) : ComponentManager(engine_core){};

    ~BehaviourManager() override = default;

    void init() override;
    void update() override;
    void exit() override;
};
