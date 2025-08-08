#include "../../include/entities/entity2D.hpp"

#include "../../include/components/graphics_component.hpp"
#include "../../include/components/transform_component.hpp"

Entity2D::Entity2D(GameCore *game_core, RenderingMode rendering_mode) : Entity(game_core) {
    this->_transform_component = this->create_component<TransformComponent>();
    this->_graphics_component = this->create_component<GraphicsComponent>(rendering_mode);
}