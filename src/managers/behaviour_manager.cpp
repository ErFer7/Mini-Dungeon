#include "../../include/managers/behaviour_manager.hpp"

#include "../../include/components/behaviour_component.hpp"

void BehaviourManager::init() {}

void BehaviourManager::update() {
    ComponentVector *components = this->get_components();

    for (auto component : *components) {
        BehaviourComponent *behaviour_component = static_cast<BehaviourComponent *>(component);

        behaviour_component->update();
    }
}

void BehaviourManager::exit() {}
