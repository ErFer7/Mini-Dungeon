#pragma once

#include "scene.hpp"
#include "types.hpp"
#include "utils/id.hpp"

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
    utils::Handle<Player> _player;
    utils::Handle<Wall> _wall;
};
