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

    TextComponent(TextComponent &&other) noexcept : Component(std::move(other)) { this->_move(std::move(other)); }

    ~TextComponent() override;

    inline TextComponent &operator=(TextComponent &&other) noexcept {
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
    void _move(TextComponent &&other);

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
