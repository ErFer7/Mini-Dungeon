#include "../../../include/entities/user_interface/ui_entity.hpp"

#include "../../../include/components/graphics_component.hpp"
#include "../../../include/components/ui_transform_component.hpp"

// TODO: Check the order of initialization of the sizes and everything else
UIEntity::UIEntity(GameCore *game_core,
                   Texture2D texture,
                   UIOrigin ui_origin,
                   Vector2 position,
                   float rotation,
                   Vector2 scale,
                   Color color,
                   int layer,
                   UITransformComponent *parent_ui_transform)
    : Entity2D(game_core, texture, RenderingMode::SCREEN_SPACE, position, rotation, scale, color, layer) {
    this->_ui_transform_component = this->create_component<UITransformComponent>(ui_origin, parent_ui_transform, position, rotation, scale);
}
