#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

using utils::GameCoreDependencyInjector;

class TextureContainer final : public MapContainer<std::string, Texture2D> {
   public:
    TextureContainer() = default;

    TextureContainer(GameCore *game_core) : MapContainer<std::string, Texture2D>(game_core) {}

    virtual ~TextureContainer() override = default;

   public:
    Texture2D load_texture(std::string path);

    void unload_all_textures();
};