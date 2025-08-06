#pragma once

#include <memory>

#include "managers/manager.hpp"
#include "scenes/init_scene.hpp"

class GameManager : public Manager {
   public:
    GameManager();

    GameManager(GameCore *game_core);

    ~GameManager();

    void init() override;

    void update() override;

    void exit() override {};

   private:
    std::unique_ptr<InitScene> _init_scene;
    Scene *_current_scene;
};
