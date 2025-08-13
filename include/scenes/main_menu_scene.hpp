#pragma once

#include "../entities/user_interface/background.hpp"
#include "../entities/user_interface/text.hpp"
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
    Background *_background;
    Text *_title;
    Text *_version;
};
