#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "containers/component_containers/heap_allocated_component_container.hpp"
#include "managers/manager.hpp"

class BehaviorManager : public Manager {
    friend class BehaviorComponent;

   public:
    typedef std::vector<std::unique_ptr<BehaviorComponent>> BehaviorComponentVector;

   public:
    BehaviorManager() = default;

    ~BehaviorManager() override = default;

    void init() override;
    void update() override;
    void exit() override;

   private:
    BehaviorComponentContainer *_behavior_component_container;
};
