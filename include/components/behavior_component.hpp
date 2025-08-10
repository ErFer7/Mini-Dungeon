#pragma once

#include "../types.hpp"
#include "component.hpp"

class BehaviorComponent : public Component {
   public:
    BehaviorComponent(GameCore *game_core, Entity *entity) : Component(game_core, entity) {}

    ~BehaviorComponent() override;

    virtual void start() = 0;

    virtual void update() = 0;

   protected:
    void register_component() override;

    void unregister_component() override;
};
