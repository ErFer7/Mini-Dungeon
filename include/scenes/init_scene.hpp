#pragma once

#include "../utils/game_core_dependency_injector.hpp"
#include "scene.hpp"

class InitScene : public Scene {
   public:
    InitScene() = default;

    InitScene(GameCore *game_core) : Scene(game_core){};

    ~InitScene(){};

    void init() override {};

    void update() override {};

    void exit() override {};
};
