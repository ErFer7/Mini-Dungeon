#include <memory>

#include "components/behavior_components/behavior_component.hpp"
#include "game_core.hpp"
#include "managers/behavior_component_manager.hpp"

void BehaviorComponentManager::init() {
    this->_behavior_component_container = GameCore::get_instance()->get_behavior_component_container();
}

void BehaviorComponentManager::update() {
    for (auto &component : *this->_behavior_component_container->get_data_structure()) {
        BehaviorComponent *behavior_component = static_cast<BehaviorComponent *>(component.get());

        if (behavior_component->is_active()) {
            behavior_component->update();
        }
    }
}

void BehaviorComponentManager::exit() {}
