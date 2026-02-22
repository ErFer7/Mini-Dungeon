#include "containers/asset_containers/image_container.hpp"

Image ImageContainer::load_image(std::string path) {
    if (this->contains(path)) {
        return this->get(path);
    }

    this->insert(path.c_str(), LoadImage(path.c_str()));

    return this->get(path);
}

void ImageContainer::unload_all_images() {
    for (auto [_, font] : *this->get_data_structure()) {
        if (IsImageValid(font)) {
            UnloadImage(font);
        }
    }
}