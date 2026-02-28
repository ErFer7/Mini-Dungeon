#include "containers/asset_containers/font_container.hpp"

Font FontContainer::load_font(std::string name,
                              std::string path,
                              int font_size,
                              int *code_points,
                              int code_point_count) {
    if (this->contains(name)) {
        return this->get(name);
    }

    this->insert(name.c_str(), LoadFontEx(path.c_str(), font_size, code_points, code_point_count));

    return this->get(name);
}

void FontContainer::unload_fonts() {
    for (auto [_, font] : *this->get_data_structure()) {
        if (IsFontValid(font)) {
            UnloadFont(font);
        }
    }
}
