#include "../../../include/entities/user_interface/ui_entity.hpp"

#include "../../../include/components/graphics_component.hpp"
#include "../../../include/components/ui_transform_component.hpp"
#include "entities/entity2D.hpp"

// TODO: Check the order of initialization of the sizes and everything else
UIEntity::UIEntity(GameCore *game_core, const UIEntityArgs &args)
    : Entity2D(game_core,
               Entity2DArgs{args.texture, RenderingMode::SCREEN_SPACE, args.position, args.rotation, args.scale, args.color, args.layer}) {
    this->_ui_transform_component = this->create_component<UITransformComponent>(
        UITransformComponentArgs{args.ui_origin, args.parent_ui_transform, args.position, args.rotation, args.scale});
    this->set_activity_state_parent(args.parent_activity_state);
}
