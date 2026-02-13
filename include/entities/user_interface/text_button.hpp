#pragma once

#include "components/text_component.hpp"
#include "components/ui_transform_component.hpp"
#include "entities/user_interface/button.hpp"
#include "entities/user_interface/text.hpp"

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
    utils::Handle<UITransformComponent> parent_ui_transform = utils::Handle<UITransformComponent>();
    UIOrigin text_ui_origin = UIOrigin::CENTER;
    int font_size = 0;
    Vector2Df text_position = Vector2Df();
    float text_rotation = 0.0f;
    Vector2Df text_scale = Vector2Df(1.0f);
    Color text_color = WHITE;
    float spacing = 1.0f;
    utils::Handle<ActivityState> parent_activity_state = utils::Handle<ActivityState>();
    float texture_scale = 1.0f;

    operator ButtonArgs() const {
        return ButtonArgs{texture,
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

    operator TextArgs() const {
        return TextArgs{content,
                        font,
                        text_ui_origin,
                        font_size,
                        text_position,
                        text_rotation,
                        text_scale,
                        text_color,
                        0,
                        utils::Handle<UITransformComponent>(),
                        spacing,
                        utils::Handle<ActivityState>(),
                        texture_scale};
    }
};

class TextButton : public Button {
   public:
    TextButton(const TextButtonArgs &args);

    ~TextButton() override;

    inline utils::Handle<Text> get_text() { return this->_text; }

   private:
    utils::Handle<Text> _text;
};
