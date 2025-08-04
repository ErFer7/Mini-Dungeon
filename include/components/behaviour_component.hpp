#pragma once

#include "../types.hpp"
#include "component.hpp"

class BehaviourComponent : public Component {
   public:
    BehaviourComponent(EngineCore *engine_core, Entity *entity, bool unique) : Component(engine_core, entity, unique) {}

    ~BehaviourComponent() override;

    virtual void start() = 0;

    virtual void update() = 0;

   protected:
    void register_component() override;

    void unregister_component() override;
};