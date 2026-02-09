#pragma once

#include "scene.hpp"
#include "types.hpp"

class GameplayScene : public Scene {
   public:
    GameplayScene() = default;

    ~GameplayScene() {};

    void init() override;

    void enter() override;

    void update() override {};

    void leave() override {};

    void exit() override {};

   private:
    Player *_player;
    Wall *_wall;
};
