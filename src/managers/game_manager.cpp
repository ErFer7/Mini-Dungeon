#include "../../include/managers/game_manager.hpp"

#include "../../include/scenes/menu_scene.hpp"
#include "scenes/gameplay_scene.hpp"

GameManager::GameManager(GameCore *game_core) : Manager(game_core) {
    this->_menu_scene = this->create_unique<MenuScene>();
    this->_gameplay_scene = this->create_unique<GameplayScene>();
}

GameManager::~GameManager() { this->_menu_scene.reset(); }

void GameManager::init() {
    this->_current_scene = _menu_scene.get();

    this->_current_scene->init();
    this->_current_scene->enter();
}

void GameManager::update() { this->_current_scene->update(); }

void GameManager::_transition(Scene *next_scene) {
    this->_current_scene->leave();

    this->_current_scene = next_scene;

    if (!this->_current_scene->was_initialized()) {
        this->_current_scene->init();
    }

    this->_current_scene->enter();
}
