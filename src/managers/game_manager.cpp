#include "managers/game_manager.hpp"

#include "scenes/gameplay_scene.hpp"
#include "scenes/menu_scene.hpp"

GameManager::GameManager() {
    this->_menu_scene = std::make_unique<MenuScene>();
    this->_gameplay_scene = std::make_unique<GameplayScene>();
}

GameManager::~GameManager() { this->_menu_scene.reset(); }

void GameManager::init() {
    this->_current_scene = _menu_scene.get();

    this->_current_scene->init();
    this->_current_scene->enter();
    this->_gameplay_scene->init();  // TODO: Find out why this is necessary and initialize this somewhere else
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
