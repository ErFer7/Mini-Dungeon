#pragma once

#include "../../components/button_component.hpp"
#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "ui_entity.hpp"

class Button : public UIEntity {
   public:
    Button(GameCore *game_core,
           Texture2D texture,
           UIOrigin ui_origin,
           Vector2 position = Vector2Zero(),
           float rotation = 0.0f,
           Vector2 scale = Vector2One(),
           Color color = WHITE,
           int layer = 0,
           UITransformComponent *parent_ui_transform = nullptr);

    ~Button() override = default;

    inline ButtonComponent *get_button_component() { return this->_button_component; }

   private:
    ButtonComponent *_button_component;
};
