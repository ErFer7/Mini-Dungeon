#include "../../include/components/text_component.hpp"

#include "raylib.h"

TextComponent::TextComponent(GameCore *game_core, Entity *entity, string content, Font font, int font_size, float spacing, Color color)
    : Component(game_core, entity),
      _content(content),
      _font(font),
      _spacing(spacing),
      _color(color),
      _text_image(Image()),
      _text_texture(Texture2D()) {
    this->_font_size = font_size != 0 ? font_size : font.baseSize;
    this->_graphics_component = entity->get_component<GraphicsComponent>();

    this->_update_texture();
}

TextComponent::~TextComponent() {
    this->unregister_component();

    if (IsImageValid(this->_text_image)) {
        UnloadImage(this->_text_image);
    }

    if (IsTextureValid(this->_text_texture)) {
        UnloadTexture(this->_text_texture);
    }
}

void TextComponent::set_content(string content) {
    this->_content = content;
    this->_update_texture();
}

void TextComponent::set_font(Font font) {
    this->_font = font;
    this->_update_texture();
}

void TextComponent::set_font_size(int font_size) {
    this->_font_size = font_size;
    this->_update_texture();
}

void TextComponent::set_spacing(float spacing) {
    this->_spacing = spacing;
    this->_update_texture();
}

void TextComponent::set_color(Color color) {
    this->_color = color;
    this->_update_texture();
}

void TextComponent::_update_texture() {
    if (IsImageValid(this->_text_image)) {
        UnloadImage(this->_text_image);
    }

    if (IsTextureValid(this->_text_texture)) {
        UnloadTexture(this->_text_texture);
    }

    this->_text_image = ImageTextEx(this->_font, this->_content.c_str(), this->_font_size, this->_spacing, this->_color);
    this->_text_texture = LoadTextureFromImage(this->_text_image);

    this->_graphics_component->set_texture(this->_text_texture);
}
