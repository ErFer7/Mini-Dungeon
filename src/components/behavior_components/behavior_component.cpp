#include "components/behavior_components/behavior_component.hpp"

#include "game_core.hpp"
#include "managers/behavior_component_manager.hpp"

BehaviorComponent::~BehaviorComponent() {
    log_info("BehaviorComponent::~BehaviorComponent()");

    this->unregister_component();
}

void BehaviorComponent::register_component() {
    log_info("BehaviorComponent::register_component()");

    this->get_game_core()->get_behavior_component_manager()->register_component(this);
}

void BehaviorComponent::unregister_component() {
    log_info("BehaviorComponent::unregister_component()");

    this->get_game_core()->get_behavior_component_manager()->unregister_component(this);
}