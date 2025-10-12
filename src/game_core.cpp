#include "game_core.hpp"

#include <raylib.h>

GameCore::GameCore(int screen_width, int screen_height, const char *title, int target_fps, bool resizable, bool fullscreen, bool show_fps)
    : _entity_container(this),
      _asset_container(this),
      _game_manager(this),
      _behavior_component_manager(this),
      _physics_component_manager(this),
      _graphics_component_manager(this, screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps),
      _is_exiting(false) {}

void GameCore::init_main_loop() {
    this->_behavior_component_manager.init();
    this->_physics_component_manager.init();
    this->_graphics_component_manager.init();
    this->_game_manager.init();

    while (!WindowShouldClose() && !_is_exiting) {
        this->_game_manager.update();
        this->_behavior_component_manager.update();
        this->_physics_component_manager.update();
        this->_graphics_component_manager.update();
    }

    this->_entity_container.free();
    this->_asset_container.free();
    this->_graphics_component_manager.exit();
    this->_behavior_component_manager.exit();
    this->_physics_component_manager.exit();
    this->_game_manager.exit();
}
