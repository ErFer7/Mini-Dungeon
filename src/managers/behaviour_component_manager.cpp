#include "../../include/components/behavior_component.hpp"
#include "../../include/managers/behavior_component_manager.hpp"

void BehaviorComponentManager::init() {}

void BehaviorComponentManager::update() {
    ComponentVector *components = this->get_components();

    for (auto component : *components) {
        BehaviorComponent *behaviour_component = static_cast<BehaviorComponent *>(component);

        if (behaviour_component->is_active()) {
            behaviour_component->update();
        }
    }
}

void BehaviorComponentManager::exit() {}
