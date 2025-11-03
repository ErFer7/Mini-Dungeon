#pragma once

#include <memory>
#include <vector>

#include "components/behavior_components/behavior_component.hpp"
#include "containers/component_containers/heap_allocated_component_container.hpp"
#include "managers/manager.hpp"

using std::make_unique;
using std::unique_ptr;
using std::vector;

class BehaviorComponentManager : public Manager {
    friend class BehaviorComponent;

   public:
    typedef vector<unique_ptr<BehaviorComponent>> BehaviorComponentVector;

   public:
    BehaviorComponentManager() = default;

    BehaviorComponentManager(GameCore *game_core) : Manager(game_core) {}

    ~BehaviorComponentManager() override = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    BehaviorComponentContainer *_behavior_component_container;
};
