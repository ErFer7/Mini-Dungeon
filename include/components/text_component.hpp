#pragma once

#include <string>

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "component.hpp"
#include "graphics_component.hpp"
#include "raylib.h"

using std::string;

class TextComponent : public Component {
   public:
    TextComponent(GameCore *game_core,
                  Entity *entity,
                  string content,
                  Font font,
                  int font_size = 0,
                  float spacing = 1.0f,
                  Color color = WHITE);

    ~TextComponent() override;

    inline string get_content() const { return this->_content; }

    void set_content(string content);

    inline Font get_font() const { return this->_font; }

    void set_font(Font font);

    inline int get_font_size() const { return this->_font_size; }

    void set_font_size(int font_size);

    inline float get_spacing() const { return this->_spacing; }

    void set_spacing(float spacing);

    inline Color get_color() const { return this->_color; }

    void set_color(Color color);

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    void _update_texture();

   private:
    string _content;
    Font _font;
    int _font_size;
    float _spacing;
    Color _color;
    GraphicsComponent *_graphics_component;
    Image _text_image;
    Texture2D _text_texture;
};
