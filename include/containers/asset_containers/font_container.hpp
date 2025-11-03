#pragma once

#include <raylib.h>

#include "containers/map_container.hpp"

using utils::GameCoreDependencyInjector;

class FontContainer final : public MapContainer<std::string, Font> {
   public:
    FontContainer() = default;

    FontContainer(GameCore *game_core) : MapContainer<std::string, Font>(game_core) {}

    // TODO: Add an error message saying that at this point there shouldn't be any font
    virtual ~FontContainer() override = default;

   public:
    Font load_font(std::string name,
                   std::string path,
                   int font_size,
                   int *code_points = nullptr,
                   int code_point_count = 0);

    void unload_all_fonts();
};