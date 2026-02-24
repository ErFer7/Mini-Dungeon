#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

class TextureContainer final : public MapContainer<std::string, Texture2D> {
   public:
    TextureContainer() : MapContainer<std::string, Texture2D>() {}

    ~TextureContainer() override = default;

   public:
    Texture2D load_texture(std::string path);

    void unload_textures();
};
