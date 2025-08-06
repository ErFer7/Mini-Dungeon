#include "../../include/managers/game_manager.hpp"

#include "managers/game_manager.hpp"
#include "managers/manager.hpp"
#include "scenes/init_scene.hpp"

GameManager::GameManager(GameCore *game_core) : Manager(game_core) { this->_init_scene = this->create_unique<InitScene>(); }

void GameManager::init() {
    this->_current_scene = _init_scene.get();

    this->_current_scene->init();
}

void GameManager::update() { this->_current_scene->update(); }
