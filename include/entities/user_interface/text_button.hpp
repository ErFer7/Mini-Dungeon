#pragma once

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "button.hpp"
#include "components/text_component.hpp"
#include "text.hpp"
#include "utils/vector.hpp"

using std::string;
using utils::Vector2Df;

struct TextButtonArgs {
    Texture2D texture;
    UIOrigin ui_origin;
    string content;
    Font font;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    UITransformComponent *parent_ui_transform = nullptr;
    UIOrigin text_ui_origin = UIOrigin::CENTER;
    int font_size = 0;
    Vector2Df text_position = Vector2Df();
    float text_rotation = 0.0f;
    Vector2Df text_scale = Vector2Df(1.0f);
    Color text_color = WHITE;
    float spacing = 1.0f;
    ActivityState *parent_activity_state = nullptr;
};

class TextButton : public Button {
   public:
    TextButton(GameCore *game_core, const TextButtonArgs &args);

    ~TextButton() override;

    inline Text *get_text() { return this->_text; }

   private:
    Text *_text;
};
