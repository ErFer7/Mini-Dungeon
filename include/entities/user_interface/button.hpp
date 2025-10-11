#pragma once

#include "../../components/button_component.hpp"
#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "ui_entity.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct ButtonArgs {
    Texture2D texture;
    UIOrigin ui_origin;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    UITransformComponent *parent_ui_transform = nullptr;
    ActivityState *parent_activity_state = nullptr;
};

class Button : public UIEntity {
   public:
    Button(GameCore *game_core, const ButtonArgs &args);

    ~Button() override = default;

    inline ButtonComponent *get_button_component() { return this->_button_component; }

   private:
    ButtonComponent *_button_component;
};
