#pragma once

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "ui_entity.hpp"

class Text : public UIEntity {
   public:
    Text(GameCore *game_core, UIOrigin ui_origin, UITransformComponent *parent_ui_transform = nullptr);

    ~Text() override = default;
};
