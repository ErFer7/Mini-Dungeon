#include "../../include/managers/game_manager.hpp"

#include "../../include/scenes/main_menu_scene.hpp"

GameManager::GameManager(GameCore *game_core) : Manager(game_core) { this->_main_menu_scene = this->create_unique<MainMenuScene>(); }

GameManager::~GameManager() {
    this->_main_menu_scene.reset();
}

void GameManager::init() {
    this->_current_scene = _main_menu_scene.get();

    this->_current_scene->init();
}

void GameManager::update() { this->_current_scene->update(); }
