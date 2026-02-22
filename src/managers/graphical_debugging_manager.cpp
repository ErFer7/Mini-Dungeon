#include "managers/graphical_debugging_manager.hpp"

#include "game_core.hpp"
#include "raylib.h"

void GraphicalDebuggingManager::init() {
    this->_transform_component_container = GameCore::get_transform_component_container();
    this->_collider_component_container = GameCore::get_collider_component_container();
    this->_physics_component_container = GameCore::get_physics_component_container();
}

void GraphicalDebuggingManager::update() {
    BeginMode2D(GameCore::get_graphics_manager()->get_camera2D());

    for (auto &component : *this->_transform_component_container->get_data_structure()) {
        component.debug_draw();
    }

    for (auto &component : *this->_physics_component_container->get_data_structure()) {
        component.debug_draw();
    }

    for (auto &component : *this->_collider_component_container->get_data_structure()) {
        component.debug_draw();
    }

    EndMode2D();
}
