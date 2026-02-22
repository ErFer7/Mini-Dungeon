#pragma once

#include "managers/manager.hpp"
#include "types.hpp"

class GraphicalDebuggingManager final : public Manager {
   public:
    GraphicalDebuggingManager() = default;

    ~GraphicalDebuggingManager() override = default;

    void init() override;

    void update() override;

    void exit() override {}

   private:
    TransformComponentContainer *_transform_component_container;
    ColliderComponentContainer *_collider_component_container;
    PhysicsComponentContainer *_physics_component_container;
};
