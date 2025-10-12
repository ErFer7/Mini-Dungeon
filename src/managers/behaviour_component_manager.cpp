#include "components/behavior_components/behavior_component.hpp"
#include "managers/behavior_component_manager.hpp"

void BehaviorComponentManager::init() {}

void BehaviorComponentManager::update() {
    ComponentVector *components = this->get_components();

    for (auto component : *components) {
        BehaviorComponent *behavior_component = static_cast<BehaviorComponent *>(component);

        if (behavior_component->is_active()) {
            behavior_component->update();
        }
    }
}

void BehaviorComponentManager::exit() {}
