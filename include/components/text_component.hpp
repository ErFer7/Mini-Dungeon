#pragma once

#include <string>

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "component.hpp"
#include "graphics_component.hpp"

using std::string;

class TextComponent : public Component {
   public:
    TextComponent(GameCore *game_core, Entity *entity);

    ~TextComponent() override { this->unregister_component(); };

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    string _content;
    GraphicsComponent *_graphics_component;
};