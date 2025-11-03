#include "entities/static_physical_entity2D.hpp"

#include "components/collider_component.hpp"
#include "entities/entity2D.hpp"

StaticPhysicalEntity2D::StaticPhysicalEntity2D(GameCore *game_core, const StaticPhysicalEntity2DArgs &args)
    : Entity2D(game_core, static_cast<Entity2DArgs>(args)) {
    this->_collider_component = this->create_component<ColliderComponent>(static_cast<ColliderComponentArgs>(args));
}