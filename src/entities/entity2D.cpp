#include "../../include/entities/entity2D.hpp"

#include "../../include/components/graphics_component.hpp"
#include "../../include/components/transform_component.hpp"

Entity2D::Entity2D(GameCore *game_core,
                   Texture2D texture,
                   RenderingMode rendering_mode,
                   Vector2 position,
                   float rotation,
                   Vector2 scale,
                   Color color,
                   int layer)
    : Entity(game_core) {
    this->_transform_component = this->create_component<TransformComponent>(position, rotation, scale);
    this->_graphics_component = this->create_component<GraphicsComponent>(texture, rendering_mode, color, layer);
}