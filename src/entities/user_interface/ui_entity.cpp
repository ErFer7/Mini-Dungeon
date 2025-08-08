#include "../../../include/entities/user_interface/ui_entity.hpp"

#include "../../../include/components/ui_transform_component.hpp"

// TODO: Check the order of initialization of the sizes and everything else
UIEntity::UIEntity(GameCore *game_core, Entity *parent, UIOrigin ui_origin, UITransformComponent *parent_ui_transform)
    : Entity2D(game_core, parent) {
    this->_ui_transform_component = this->create_component<UITransformComponent>(ui_origin, parent_ui_transform);
}
