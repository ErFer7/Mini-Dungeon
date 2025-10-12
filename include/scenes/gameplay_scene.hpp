#pragma once

#include "entities/gameplay/player.hpp"
#include "scene.hpp"

class GameplayScene : public Scene {
   public:
    GameplayScene() = default;

    GameplayScene(GameCore *game_core) : Scene(game_core){};

    ~GameplayScene(){};

    void init() override;

    void enter() override;

    void update() override {};

    void leave() override {};

    void exit() override {};

   private:
    Player *_player;
};
