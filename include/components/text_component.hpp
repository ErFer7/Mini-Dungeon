#pragma once

#include <raylib.h>

#include <string>

#include "components/component.hpp"
#include "components/graphics_component.hpp"

using utils::Handle;

struct TextComponentArgs {
    std::string content;
    Font font;
    int font_size = 0;
    float spacing = 1.0f;
    Color color = WHITE;
};

class TextComponent final : public Component {
   public:
    TextComponent(Handle<Entity> entity, const TextComponentArgs &args);

    TextComponent(TextComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~TextComponent() override;

    TextComponent &operator=(TextComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline std::string get_content() const { return this->_content; }

    void set_content(std::string content);

    inline Font get_font() const { return this->_font; }

    void set_font(Font font);

    inline int get_font_size() const { return this->_font_size; }

    void set_font_size(int font_size);

    inline float get_spacing() const { return this->_spacing; }

    void set_spacing(float spacing);

    inline Color get_color() const { return this->_color; }

    void set_color(Color color);

    void debug_draw() override {}

   private:
    void _move(TextComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_content = std::move(other._content);
        this->_font = std::move(other._font);
        this->_font_size = std::move(other._font_size);
        this->_spacing = std::move(other._spacing);
        this->_color = std::move(other._color);
        this->_graphics_component = std::move(other._graphics_component);
        this->_text_image = std::move(other._text_image);
        this->_text_texture = std::move(other._text_texture);
    }

    void _update_texture();

   private:
    std::string _content;
    Font _font;
    int _font_size;
    float _spacing;
    Color _color;
    Handle<GraphicsComponent> _graphics_component;
    Image _text_image;
    Texture2D _text_texture;
};
