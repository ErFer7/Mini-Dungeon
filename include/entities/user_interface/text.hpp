#pragma once

#include <string>

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "components/text_component.hpp"
#include "ui_entity.hpp"

using std::string;

class Text : public UIEntity {
   public:
    Text(GameCore *game_core,
         string content,
         Font font,
         UIOrigin ui_origin,
         int font_size = 0,
         Vector2 position = Vector2Zero(),
         float rotation = 0.0f,
         Vector2 scale = Vector2One(),
         Color color = WHITE,
         int layer = 0,
         UITransformComponent *parent_ui_transform = nullptr,
         float spacing = 1.0f);

    ~Text() override = default;

    inline TextComponent *get_text_component() { return this->_text_component; }

   private:
    TextComponent *_text_component;
};
