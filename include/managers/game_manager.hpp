#pragma once

#include <memory>

#include "../types.hpp"
#include "manager.hpp"

class GameManager : public Manager {
   public:
    GameManager(GameCore *game_core);

    ~GameManager();

    void init() override;

    void update() override;

    void exit() override {};

   private:
    std::unique_ptr<MainMenuScene> _main_menu_scene;
    Scene *_current_scene;
};
