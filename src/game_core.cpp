#include "../include/game_core.hpp"

#include <memory>

#include "raylib.h"

GameCore::GameCore(int screen_width, int screen_height, const char *title, int target_fps, bool resizable, bool fullscreen, bool show_fps) {
    this->_entity_container = std::make_unique<EntityContainer>(this);
    this->_behaviour_manager = std::make_unique<BehaviourManager>(this);
    this->_graphics_manager =
        std::make_unique<GraphicsManager>(this, screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);
}

GameCore::~GameCore() {
    this->_entity_container.reset();
    this->_graphics_manager.reset();
    this->_behaviour_manager.reset();
    this->_main_behaviour_manager.reset();
}

void GameCore::init_main_loop() {
    this->_behaviour_manager->init();
    this->_graphics_manager->init();
    this->_main_behaviour_manager->init();

    while (!WindowShouldClose()) {
        this->_main_behaviour_manager->update();
        this->_behaviour_manager->update();
        this->_graphics_manager->update();
    }

    this->_main_behaviour_manager->exit();
    this->_graphics_manager->exit();
    this->_behaviour_manager->exit();
}
