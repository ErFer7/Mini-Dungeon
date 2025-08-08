#pragma once

#include "../entities/user_interface/ui_entity.hpp"
#include "scene.hpp"

class MainMenuScene : public Scene {
   public:
    MainMenuScene() = default;

    MainMenuScene(GameCore *game_core) : Scene(game_core){};

    ~MainMenuScene(){};

    void init() override;

    void update() override {};

    void exit() override;

   private:
    UIEntity *_test_entity;
};
