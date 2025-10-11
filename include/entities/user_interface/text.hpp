#pragma once

#include <string>

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "components/text_component.hpp"
#include "ui_entity.hpp"
#include "utils/vector.hpp"

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
};

class Text : public UIEntity {
   public:
    Text(GameCore *game_core, const TextArgs &args);

    ~Text() override = default;

    inline TextComponent *get_text_component() { return this->_text_component; }

   private:
    TextComponent *_text_component;
};
