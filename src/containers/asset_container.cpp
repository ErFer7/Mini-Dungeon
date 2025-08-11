#include "../../include/containers/asset_container.hpp"

#include <memory>

#include "raylib.h"

using std::make_unique;

AssetContainer::AssetContainer(GameCore *game_core) : GameCoreDependencyInjector(game_core) {
    this->_texture_map = make_unique<TextureMap>();
    this->_font_map = make_unique<FontMap>();
}

AssetContainer::~AssetContainer() {
    for (auto [_, texture] : *this->_texture_map) {
        UnloadTexture(texture);
    }

    for (auto [_, font] : *this->_font_map) {
        UnloadFont(font);
    }
}

Texture2D AssetContainer::load_texture(string path) {
    if (this->_texture_map->contains(path)) {
        return (*this->_texture_map)[path];
    }

    (*this->_texture_map)[path] = LoadTexture(path.c_str());

    return (*this->_texture_map)[path];
}

Font AssetContainer::load_font(string path) {
    if (this->_font_map->contains(path)) {
        return (*this->_font_map)[path];
    }

    (*this->_font_map)[path] = LoadFont(path.c_str());

    return (*this->_font_map)[path];
}