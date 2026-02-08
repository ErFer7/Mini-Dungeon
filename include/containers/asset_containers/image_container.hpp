#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

class ImageContainer final : public MapContainer<std::string, Image> {
   public:
    ImageContainer() : MapContainer<std::string, Image>() {}

    ~ImageContainer() override = default;

   public:
    Image load_image(std::string path);

    // TODO: Remove the usage of "all" from places like this
    void unload_all_images();
};
