#pragma once

#include "components/component.hpp"
#include "utils/debug.hpp"

using utils::log_info;

class BehaviorComponent : public Component {
   public:
    BehaviorComponent(GameCore *game_core, Entity *entity) : Component(game_core, entity) {
        log_info("BehaviorComponent::BehaviorComponent(", game_core, ", ", entity, ')');
    }

    ~BehaviorComponent() override;

    virtual void start() = 0;

    virtual void update() = 0;

   protected:
    void register_component() override;

    void unregister_component() override;
};
