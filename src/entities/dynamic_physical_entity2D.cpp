#include "entities/dynamic_physical_entity2D.hpp"

#include "components/physics_component.hpp"
#include "entities/static_physical_entity2D.hpp"

DynamicPhysicalEntity2D::DynamicPhysicalEntity2D(const DynamicPhysicalEntity2DArgs &args)
    : StaticPhysicalEntity2D(static_cast<StaticPhysicalEntity2DArgs>(args)) {
    this->_physics_component = this->create_component<PhysicsComponent>(static_cast<PhysicsComponentArgs>(args));
}
