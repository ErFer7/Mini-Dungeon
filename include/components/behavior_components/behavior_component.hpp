#pragma once

#include "components/component.hpp"
#include "managers/behavior_component_manager.hpp"
#include "utils/debug.hpp"

class BehaviorComponent : public Component {
    friend class BehaviorComponentManager;

   public:
    BehaviorComponent(GameCore *game_core, Entity *entity) : Component(game_core, entity) {
        utils::log_info("BehaviorComponent::BehaviorComponent(", game_core, ", ", entity, ')');
    }

    ~BehaviorComponent() override { utils::log_info("BehaviorComponent::~BehaviorComponent()"); };

    virtual void start() {};

    virtual void update() {};

   protected:
    void destroy() override;
};
