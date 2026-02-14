#pragma once

#include "components/component.hpp"
#include "managers/behavior_component_manager.hpp"
#include "utils/debug.hpp"

class BehaviorComponent : public Component {
    friend class BehaviorComponentManager;

   public:
    BehaviorComponent(Entity *entity) : Component(entity) { utils::log_trace(this, __FUNCTION__, entity); }

    BehaviorComponent(BehaviorComponent &&other) = default;

    ~BehaviorComponent() override { utils::log_trace(this, __FUNCTION__); };

    BehaviorComponent &operator=(BehaviorComponent &&other) = default;

    virtual void start() {};

    virtual void update() {};
};
