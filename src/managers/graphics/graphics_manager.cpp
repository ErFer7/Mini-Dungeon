#include "managers/graphics/graphics_manager.hpp"

#include "components/graphics_component.hpp"
#include "definitions.hpp"
#include "raylib.h"

GraphicsManager::GraphicsManager(int screen_width,
                                 int screen_height,
                                 const char *title,
                                 int target_fps,
                                 bool resizable,
                                 bool fullscreen,
                                 bool show_fps) {
    this->_screen_width = screen_width;
    this->_screen_height = screen_height;
    this->_title = title;
    this->_resizable = resizable;
    this->_fullscreen = fullscreen;
    this->_show_fps = show_fps;
    this->_target_fps = target_fps;
    this->_camera2D = {Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f}, 0.0f, 1.0f};
}

void GraphicsManager::init() {
    InitWindow(this->_screen_width, this->_screen_height, this->_title.c_str());

    if (this->_resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    if (this->_fullscreen) {
        ToggleFullscreen();
    }

    SetTargetFPS(this->_target_fps);

    this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};

    if constexpr (VISUALLY_DEBUGGED) {
        this->_graphical_debugging_manager.init();
    }
}

void GraphicsManager::update() {
    if (IsWindowResized()) {
        this->_screen_width = GetScreenWidth();
        this->_screen_height = GetScreenHeight();
        this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};
        this->_on_screen_resize.invoke(this->_screen_width, this->_screen_height);
    }

    this->_world_space2D.sort();
    this->_screen_space.sort();

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(this->_camera2D);
    this->_world_space2D.draw();
    EndMode2D();

    if constexpr (VISUALLY_DEBUGGED) {
        this->_graphical_debugging_manager.update();
    }

    this->_screen_space.draw();

    if (this->_show_fps) {
        DrawFPS(GetScreenWidth() - 95, 10);
    }

    EndDrawing();
}

void GraphicsManager::exit() {
    if constexpr (VISUALLY_DEBUGGED) {
        this->_graphical_debugging_manager.exit();
    }

    CloseWindow();
}

void GraphicsManager::register_component_on_space(Handle<GraphicsComponent> graphics_component) {
    switch (graphics_component->get_rendering_mode()) {
        case RenderingMode::SCREEN_SPACE:
            this->_screen_space.add_component(graphics_component);
            break;
        case RenderingMode::WORLD_SPACE_2D:
            this->_world_space2D.add_component(graphics_component);
            break;
        default:
            break;
    }
}

void GraphicsManager::unregister_component_on_space(Handle<GraphicsComponent> graphics_component) {
    switch (graphics_component->get_rendering_mode()) {
        case RenderingMode::SCREEN_SPACE:
            this->_screen_space.remove_component(graphics_component);
            break;
        case RenderingMode::WORLD_SPACE_2D:
            this->_world_space2D.remove_component(graphics_component);
            break;
        default:
            break;
    }
}
