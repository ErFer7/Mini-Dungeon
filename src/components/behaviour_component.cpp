#include "../../include/components/behaviour_component.hpp"

#include <cassert>

#include "../../include/engine_core.hpp"
#include "../../include/managers/behaviour_manager.hpp"

BehaviourComponent::~BehaviourComponent() { this->unregister_component(); }

void BehaviourComponent::register_component() { this->get_engine_core()->get_behaviour_manager()->register_component(this); }

void BehaviourComponent::unregister_component() { this->get_engine_core()->get_behaviour_manager()->unregister_component(this); }