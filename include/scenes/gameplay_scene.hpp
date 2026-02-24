#pragma once

#include "gameplay/dungeon.hpp"
#include "scene.hpp"
#include "types.hpp"
#include "utils/id/handle.hpp"

using utils::Handle;

class GameplayScene final : public Scene {
   public:
    GameplayScene() = default;

    ~GameplayScene() {};

    void init() override;

    void enter() override;

    void update() override {};

    void leave() override {};

    void exit() override {};

   private:
    Handle<Player> _player;
    Dungeon _dungeon;
};
