#include "../../include/entities/entity2D.hpp"

#include "../../include/components/graphics_component.hpp"
#include "../../include/components/transform_component.hpp"

Entity2D::Entity2D(GameCore *game_core, const Entity2DArgs &args) : Entity(game_core) {
    this->_transform_component =
        this->create_component<TransformComponent>(TransformComponentArgs{args.position, args.rotation, args.scale});
    this->_graphics_component =
        this->create_component<GraphicsComponent>(GraphicsComponentArgs{args.texture, args.rendering_mode, args.color, args.layer});
}