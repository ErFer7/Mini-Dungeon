#pragma once

#include "../entities/user_interface/background.hpp"
#include "../entities/user_interface/text.hpp"
#include "components/button_component.hpp"
#include "entities/user_interface/text_button.hpp"
#include "scene.hpp"

class GameplayScene : public Scene {
   public:
    GameplayScene() = default;

    GameplayScene(GameCore *game_core) : Scene(game_core){};

    ~GameplayScene(){};

    void init() override {};

    void enter() override {};

    void update() override {};

    void leave() override {};

    void exit() override {};
};
