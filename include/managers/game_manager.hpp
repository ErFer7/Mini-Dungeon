#pragma once

#include <memory>

#include "../types.hpp"
#include "manager.hpp"
#include "scenes/gameplay_scene.hpp"
#include "scenes/menu_scene.hpp"

using std::unique_ptr;

class GameManager : public Manager {
   public:
    GameManager() = default;

    GameManager(GameCore *game_core);

    ~GameManager();

    void init() override;

    void update() override;

    void exit() override {};

    // TODO: Refactor this to make the code more flexible
    inline void transition_to_gameplay() { this->_transition(_gameplay_scene.get()); }

    inline void transition_to_menu() { this->_transition(_menu_scene.get()); }

   private:
    void _transition(Scene *next_scene);

   private:
    unique_ptr<MenuScene> _menu_scene;
    unique_ptr<GameplayScene> _gameplay_scene;
    Scene *_current_scene;
};
