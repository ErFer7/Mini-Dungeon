#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

class FontContainer final : public MapContainer<std::string, Font> {
   public:
    FontContainer() : MapContainer<std::string, Font>() {}

    // TODO: Add an error message saying that at this point there shouldn't be any font
    ~FontContainer() override = default;

   public:
    Font load_font(std::string name,
                   std::string path,
                   int font_size,
                   int *code_points = nullptr,
                   int code_point_count = 0);

    void unload_all_fonts();
};
