#pragma once

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "../entity2D.hpp"

class UIEntity : public Entity2D {
   public:
    UIEntity(GameCore *game_core, UIOrigin ui_origin, UITransformComponent *parent_ui_transform = nullptr);

    // TODO: Destroy the entity subtree
    ~UIEntity() override = default;

    inline UITransformComponent *get_ui_transform_component() { return this->_ui_transform_component; }

   private:
    UITransformComponent *_ui_transform_component;
};
