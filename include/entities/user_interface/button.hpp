#pragma once

#include "components/behavior_components/button_component.hpp"
#include "components/ui_transform_component.hpp"
#include "entities/user_interface/ui_entity.hpp"

using utils::Handle;
using utils::Vector2Df;

struct ButtonArgs {
    Texture2D texture;
    UIOrigin ui_origin;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    Handle<UITransformComponent> parent_ui_transform = Handle<UITransformComponent>();
    Handle<ActivityState> parent_activity_state = Handle<ActivityState>();
    float texture_scale = 1.0f;

    operator UIEntityArgs() const {
        return UIEntityArgs{texture,
                            ui_origin,
                            position,
                            rotation,
                            scale,
                            color,
                            layer,
                            parent_ui_transform,
                            parent_activity_state,
                            texture_scale};
    }
};

class Button : public UIEntity {
   public:
    Button(const ButtonArgs &args);

    ~Button() override = default;

    inline Handle<ButtonComponent> get_button_component() { return this->_button_component; }

   private:
    Handle<ButtonComponent> _button_component;
};
