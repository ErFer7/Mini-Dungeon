#include "managers/physics_manager.hpp"

#include <vector>

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "containers/component_containers/stack_allocated_component_container.hpp"
#include "game_core.hpp"
#include "utils/vector.hpp"

void PhysicsManager::init() {
    this->_physics_component_container = GameCore::get_physics_component_container();
    this->_collider_component_container = GameCore::get_collider_component_container();
}

void PhysicsManager::update() {
    // TODO: Check if this could be dangerous
    std::vector<PhysicsComponent> *physics_components = this->_physics_component_container->get_data_structure();
    std::vector<ColliderComponent> *collider_components = this->_collider_component_container->get_data_structure();

    for (auto it = physics_components->begin(); it != physics_components->end(); ++it) {
        if (it->is_active()) {
            it->update();
        }
    }

    // TODO: Fix this horrible implementation, this was done just to have some collision solving
    for (auto it_i = physics_components->begin(); it_i != physics_components->end(); ++it_i) {
        for (auto it_j = collider_components->begin(); it_j != collider_components->end(); ++it_j) {
            // Both didn't move in this frame
            // TODO: Clean this
            if (!it_i->is_active() || !it_j->is_active() ||
                it_i->_get_collider_component()->get_id() == it_j->get_id() ||
                it_i->is_statically_stable() && (it_j->_get_physics_component().is_null() ||
                                                 it_j->_get_physics_component()->is_statically_stable())) {
                continue;
            }

            Handle<ColliderComponent> collider_i = it_i->_get_collider_component();
            Handle<ColliderComponent> collider_j = it_j->make_handle<ColliderComponent>();

            if (!collider_i->check_collision(collider_j)) {
                continue;
            }

            collider_i->_trigger_event();
            collider_j->_trigger_event();

            if (collider_i->is_trigger() || collider_j->is_trigger()) {
                continue;
            }

            it_i->_get_transform_component()->translate(-it_i->get_velocity() * it_i->_get_time_diff());

            it_i->set_acceleration(Vector2Df());
            it_i->set_velocity(Vector2Df());

            // FIX: For now, the collision solving is kind of dumb and the objects will keep clipping, but the idea is
            // to have something so we can move on to other thigs
        }
    }
}
