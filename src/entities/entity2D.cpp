#include "entities/entity2D.hpp"

#include "components/graphics_component.hpp"
#include "components/transform_component.hpp"

Entity2D::Entity2D(GameCore *game_core, const Entity2DArgs &args) : Entity(game_core) {
    this->_transform_component = this->create_component<TransformComponent>(static_cast<TransformComponentArgs>(args));
    this->_graphics_component = this->create_component<GraphicsComponent>(static_cast<GraphicsComponentArgs>(args));
}