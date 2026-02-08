#pragma once

#include <raylib.h>

#include <string>

#include "components/text_component.hpp"
#include "components/ui_transform_component.hpp"
#include "entities/user_interface/ui_entity.hpp"

using std::string;
using utils::Vector2Df;

struct TextArgs {
    string content;
    Font font;
    UIOrigin ui_origin;
    int font_size = 0;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    UITransformComponent *parent_ui_transform = nullptr;
    float spacing = 1.0f;
    ActivityState *parent_activity_state = nullptr;
    float texture_scale = 1.0f;

    operator UIEntityArgs() const {
        return UIEntityArgs{Texture2D(),
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

    operator TextComponentArgs() const { return TextComponentArgs{content, font, font_size, spacing, color}; }
};

class Text : public UIEntity {
   public:
    Text(const TextArgs &args);

    ~Text() override = default;

    inline TextComponent *get_text_component() { return this->_text_component; }

   private:
    TextComponent *_text_component;
};
