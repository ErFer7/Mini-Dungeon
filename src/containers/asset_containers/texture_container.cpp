#include "containers/asset_containers/texture_container.hpp"

Texture2D TextureContainer::load_texture(std::string path) {
    if (this->contains(path)) {
        return this->get(path);
    }

    this->insert(path.c_str(), LoadTexture(path.c_str()));

    return this->get(path);
}

void TextureContainer::unload_textures() {
    for (auto [_, texture] : *this->get_data_structure()) {
        if (IsTextureValid(texture)) {
            UnloadTexture(texture);
        }
    }
}
