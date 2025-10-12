#pragma once

#include "components/graphics_component.hpp"
#include "components/ui_transform_component.hpp"
#include "entities/entity2D.hpp"
#include "utils/activity_state.hpp"
#include "utils/vector.hpp"

using utils::ActivityState;
using utils::Vector2Df;

struct UIEntityArgs {
    Texture2D texture;
    UIOrigin ui_origin;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    UITransformComponent *parent_ui_transform = nullptr;
    ActivityState *parent_activity_state = nullptr;
    float texture_scale = 1.0f;

    operator Entity2DArgs() const {
        return Entity2DArgs{
            texture, RenderingMode::SCREEN_SPACE, position, rotation, scale, color, layer, texture_scale};
    }

    operator UITransformComponentArgs() const {
        return UITransformComponentArgs{ui_origin, parent_ui_transform, position, rotation, scale};
    }
};

class UIEntity : public Entity2D {
   public:
    UIEntity(GameCore *game_core, const UIEntityArgs &args);

    // TODO: Destroy the entity subtree
    ~UIEntity() override = default;

    inline UITransformComponent *get_ui_transform_component() { return this->_ui_transform_component; }

   private:
    UITransformComponent *_ui_transform_component;
};
