#include "components/text_component.hpp"

#include <raylib.h>

#include "entities/entity.hpp"

TextComponent::TextComponent(Handle<Entity> entity, const TextComponentArgs &args)
    : Component(entity),
      _content(args.content),
      _font(args.font),
      _spacing(args.spacing),
      _color(args.color),
      _text_image(Image()),
      _text_texture(Texture2D()) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    int font_size = args.font_size;

    this->_font_size = font_size != 0 ? font_size : args.font.baseSize;
    this->_graphics_component = entity->get_component<GraphicsComponent>();

    this->_update_texture();
}

TextComponent::~TextComponent() {
    if (this->get_id() == -1LL) {
        return;
    }

    if (IsImageValid(this->_text_image)) {
        UnloadImage(this->_text_image);
    }

    if (IsTextureValid(this->_text_texture)) {
        UnloadTexture(this->_text_texture);
    }
}

void TextComponent::set_content(std::string content) {
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

void TextComponent::_move(TextComponent &&other) {
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

void TextComponent::_update_texture() {
    if (IsImageValid(this->_text_image)) {
        UnloadImage(this->_text_image);
    }

    if (IsTextureValid(this->_text_texture)) {
        UnloadTexture(this->_text_texture);
    }

    this->_text_image =
        ImageTextEx(this->_font, this->_content.c_str(), this->_font_size, this->_spacing, this->_color);
    this->_text_texture = LoadTextureFromImage(this->_text_image);

    this->_graphics_component->set_texture(this->_text_texture);
}
