#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

using utils::GameCoreDependencyInjector;

class ImageContainer final : public MapContainer<std::string, Image> {
   public:
    ImageContainer() = default;

    ImageContainer(GameCore *game_core) : MapContainer<std::string, Image>(game_core) {}

    virtual ~ImageContainer() override = default;

   public:
    Image load_image(std::string path);

    // TODO: Remove the usage of "all" from places like this
    void unload_all_images();
};
