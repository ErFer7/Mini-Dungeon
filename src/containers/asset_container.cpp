#include "containers/asset_container.hpp"

#include <raylib.h>

#include <memory>

using std::make_unique;

AssetContainer::AssetContainer(GameCore *game_core) : Container(game_core) {
    this->_image_map = make_unique<ImageMap>();
    this->_texture_map = make_unique<TextureMap>();
    this->_font_map = make_unique<FontMap>();
}

Image AssetContainer::load_image(string path) {
    if (this->_image_map->contains(path)) {
        return (*this->_image_map)[path];
    }

    (*this->_image_map)[path] = LoadImage(path.c_str());

    return (*this->_image_map)[path];
}

Texture2D AssetContainer::load_texture(string path) {
    if (this->_texture_map->contains(path)) {
        return (*this->_texture_map)[path];
    }

    (*this->_texture_map)[path] = LoadTexture(path.c_str());

    return (*this->_texture_map)[path];
}

Font AssetContainer::load_font(string name, string path, int font_size, int *code_points, int code_point_count) {
    if (this->_font_map->contains(name)) {
        return (*this->_font_map)[name];
    }

    (*this->_font_map)[name] = LoadFontEx(path.c_str(), font_size, code_points, code_point_count);

    return (*this->_font_map)[name];
}

void AssetContainer::free() {
    for (auto [_, image] : *this->_image_map) {
        if (IsImageValid(image)) {
            UnloadImage(image);
        }
    }

    for (auto [_, texture] : *this->_texture_map) {
        if (IsTextureValid(texture)) {
            UnloadTexture(texture);
        }
    }

    for (auto [_, font] : *this->_font_map) {
        if (IsFontValid(font)) {
            UnloadFont(font);
        }
    }
}
