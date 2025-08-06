#include "../include/game_core.hpp"

#include <memory>

#include "raylib.h"

GameCore::GameCore(int screen_width, int screen_height, const char *title, int target_fps, bool resizable, bool fullscreen, bool show_fps) {
    this->_entity_container = std::make_unique<EntityContainer>(this);
    this->_game_manager = std::make_unique<GameManager>(this);
    this->_behavior_component_manager = std::make_unique<BehaviorComponentManager>(this);
    this->_graphics_component_manager =
        std::make_unique<GraphicsComponentManager>(this, screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);
}

GameCore::~GameCore() {
    // TODO: Check if this is really necessary
    this->_entity_container.reset();
    this->_graphics_component_manager.reset();
    this->_behavior_component_manager.reset();
    this->_game_manager.reset();
}

void GameCore::init_main_loop() {
    this->_behavior_component_manager->init();
    this->_graphics_component_manager->init();
    this->_game_manager->init();

    while (!WindowShouldClose()) {
        this->_game_manager->update();
        this->_behavior_component_manager->update();
        this->_graphics_component_manager->update();
    }

    this->_graphics_component_manager->exit();
    this->_behavior_component_manager->exit();
    this->_game_manager->exit();
}
