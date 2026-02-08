#include "entities/user_interface/ui_entity.hpp"

#include "components/ui_transform_component.hpp"
#include "entities/entity2D.hpp"

// TODO: Check the order of initialization of the sizes and everything else
UIEntity::UIEntity(const UIEntityArgs &args) : Entity2D(static_cast<Entity2DArgs>(args)) {
    this->_ui_transform_component =
        this->create_component<UITransformComponent>(static_cast<UITransformComponentArgs>(args));
    this->set_activity_state_parent(args.parent_activity_state);
}
