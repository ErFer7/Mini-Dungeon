#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../utils/game_core_dependency_injector.hpp"
#include "raylib.h"

using std::string;
using std::unique_ptr;
using std::unordered_map;
using utils::GameCoreDependencyInjector;

class AssetContainer : public GameCoreDependencyInjector {
   public:
    typedef unordered_map<string, Texture2D> TextureMap;
    typedef unordered_map<string, Font> FontMap;

   public:
    AssetContainer() = default;

    AssetContainer(GameCore *game_core);

    ~AssetContainer();

    Texture2D load_texture(string path);

    Font load_font(string path);

   private:
    unique_ptr<TextureMap> _texture_map;
    unique_ptr<FontMap> _font_map;
};
