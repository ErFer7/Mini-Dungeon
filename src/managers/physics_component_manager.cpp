#include "managers/physics_component_manager.hpp"

#include <vector>

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "containers/component_containers/stack_allocated_component_container.hpp"
#include "game_core.hpp"

void PhysicsComponentManager::init() {
    this->_physics_component_container = GameCore::get_instance()->get_physics_component_container();
}

void PhysicsComponentManager::update() {
    std::vector<PhysicsComponent> *physics_components = this->_physics_component_container->get_data_structure();

    for (auto it = physics_components->begin(); it != physics_components->end(); ++it) {
        if (it->is_active()) {
            it->update();

            // This is true when the component moved in this frame
            if (!it->is_statically_stable()) {
            }
        }
    }

    // TODO: Fix this horrible implementation, this was done just to have some collision solving
    // TODO: Allow managers to manage more than one type of component
    for (auto it_i = physics_components->begin(); it_i != physics_components->end(); ++it_i) {
        for (auto it_j = it_i + 1; it_j != physics_components->end(); ++it_j) {
            // Both didn't move in this frame
            if (it_i->is_statically_stable() && it_j->is_statically_stable()) {
                continue;
            }

            Handle<ColliderComponent> collider_component_i = it_i->get_collider_component();
            Handle<ColliderComponent> collider_component_j = it_j->get_collider_component();
        }
    }
}
