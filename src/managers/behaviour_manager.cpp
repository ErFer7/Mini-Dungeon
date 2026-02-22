#include <memory>

#include "components/behavior_components/behavior_component.hpp"
#include "game_core.hpp"
#include "managers/behavior_manager.hpp"

void BehaviorManager::init() { this->_behavior_component_container = GameCore::get_behavior_component_container(); }

void BehaviorManager::update() {
    for (auto &component : *this->_behavior_component_container->get_data_structure()) {
        BehaviorComponent *behavior_component = static_cast<BehaviorComponent *>(component.get());

        if (behavior_component->is_active()) {
            behavior_component->update();
        }
    }
}

void BehaviorManager::exit() {}
