#pragma once

#include "components/component.hpp"
#include "managers/behavior_component_manager.hpp"
#include "utils/debug.hpp"

class BehaviorComponent : public Component {
    friend class BehaviorComponentManager;

   public:
    BehaviorComponent(Entity *entity) : Component(entity) { utils::log_trace(__FUNCTION__, entity); }

    ~BehaviorComponent() override { utils::log_trace(__FUNCTION__); };

    virtual void start() {};

    virtual void update() {};
};
