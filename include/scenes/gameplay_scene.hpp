#pragma once

#include "scene.hpp"
#include "types.hpp"
#include "utils/id/handle.hpp"

using utils::Handle;

class GameplayScene final : public Scene {
   public:
    GameplayScene();

    ~GameplayScene();

    void init() override;

    void enter() override;

    void update() override {};

    void leave() override {};

    void exit() override {};

   private:
    Handle<Player> _player;
    std::unique_ptr<Dungeon> _dungeon;
};
