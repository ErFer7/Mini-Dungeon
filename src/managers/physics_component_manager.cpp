#include "managers/physics_component_manager.hpp"

#include "components/physics_component.hpp"

void PhysicsComponentManager::update() {
    ComponentVector *components = this->get_components();

    for (auto component : *components) {
        PhysicsComponent *physics_component = static_cast<PhysicsComponent *>(component);

        if (physics_component->is_active()) {
            physics_component->update();
        }
    }
}