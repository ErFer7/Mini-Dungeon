#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "container.hpp"
#include "raylib.h"

using std::string;
using std::unique_ptr;
using std::unordered_map;
using utils::GameCoreDependencyInjector;

class AssetContainer : public Container {
   public:
    typedef unordered_map<string, Image> ImageMap;
    typedef unordered_map<string, Texture2D> TextureMap;
    typedef unordered_map<string, Font> FontMap;

   public:
    AssetContainer() = default;

    AssetContainer(GameCore *game_core);

    ~AssetContainer() override = default;

    Image load_image(string path);

    Texture2D load_texture(string path);

    Font load_font(string name, string path, int font_size, int *code_points = nullptr, int code_point_count = 0);

    void free() override;

   private:
    unique_ptr<ImageMap> _image_map;
    unique_ptr<TextureMap> _texture_map;
    unique_ptr<FontMap> _font_map;
};
