#include "entities/physical_entity2D.hpp"

#include "components/physics_component.hpp"
#include "entities/entity2D.hpp"

PhysicalEntity2D::PhysicalEntity2D(GameCore *game_core, const PhysicalEntity2DArgs &args)
    : Entity2D(game_core, static_cast<Entity2DArgs>(args)) {
    this->_physics_component = this->create_component<PhysicsComponent>(static_cast<PhysicsComponentArgs>(args));
}