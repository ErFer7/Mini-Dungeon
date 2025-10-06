#pragma once

#include "../../components/ui_transform_component.hpp"
#include "../../types.hpp"
#include "button.hpp"
#include "components/text_component.hpp"
#include "text.hpp"

using std::string;

struct TextButtonArgs {
    Texture2D texture;
    UIOrigin ui_origin;
    string content;
    Font font;
    Vector2 position = Vector2Zero();
    float rotation = 0.0f;
    Vector2 scale = Vector2One();
    Color color = WHITE;
    int layer = 0;
    UITransformComponent *parent_ui_transform = nullptr;
    UIOrigin text_ui_origin = UIOrigin::CENTER;
    int font_size = 0;
    Vector2 text_position = Vector2Zero();
    float text_rotation = 0.0f;
    Vector2 text_scale = Vector2One();
    Color text_color = WHITE;
    float spacing = 1.0f;
};

class TextButton : public Button {
   public:
    TextButton(GameCore *game_core, const TextButtonArgs &args);

    ~TextButton() override;

    inline Text *get_text() { return this->_text; }

   private:
    Text *_text;
};
