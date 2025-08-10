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
         UIOrigin ui_origin,
         string content,
         Font font,
         int font_size,
         UITransformComponent *parent_ui_transform = nullptr);

    ~Text() override = default;

    inline TextComponent *get_text_component() { return this->_text_component; }

   private:
    TextComponent *_text_component;
};
