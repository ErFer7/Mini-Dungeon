#include "managers/graphics_component_manager.hpp"

#include "components/graphics_component.hpp"

void Space::add_component(utils::Handle<GraphicsComponent> component) { this->_components->push_back(component); }

void Space::remove_component(utils::Handle<GraphicsComponent> component) {
    this->_components->erase(std::remove(this->_components->begin(), this->_components->end(), component),
                             this->_components->end());
}

void Space::sort() {
    switch (this->_sorting_mode) {
        case SortingMode::NONE:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](utils::Handle<GraphicsComponent> comp_a, utils::Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        case SortingMode::TOP_TO_DOWN:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](utils::Handle<GraphicsComponent> comp_a, utils::Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          if (comp_a->get_layer() == comp_b->get_layer()) {
                              return comp_a->_get_position().y < comp_b->_get_position().y;
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        case SortingMode::ISOMETRIC:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](utils::Handle<GraphicsComponent> comp_a, utils::Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          if (comp_a->get_layer() == comp_b->get_layer()) {
                              return (comp_a->_get_position().x + comp_a->_get_position().y) <
                                     (comp_b->_get_position().x + comp_b->_get_position().y);
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        default:
            break;
    }
}

void Space::draw() {
    for (auto component : *this->_components) {
        if (component->is_active()) {
            component->draw();
        }
    }
}

GraphicsComponentManager::GraphicsComponentManager(int screen_width,
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

void GraphicsComponentManager::init() {
    InitWindow(this->_screen_width, this->_screen_height, this->_title.c_str());

    if (this->_resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    if (this->_fullscreen) {
        ToggleFullscreen();
    }

    SetTargetFPS(this->_target_fps);

    this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};
}

void GraphicsComponentManager::update() {
    if (IsWindowResized()) {
        this->_screen_width = GetScreenWidth();
        this->_screen_height = GetScreenHeight();
        this->_camera2D.offset = {(float)this->_screen_width / 2.0f, (float)this->_screen_height / 2.0f};
    }

    this->_world2D_space.sort();
    this->_screen_space.sort();

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(this->_camera2D);
    this->_world2D_space.draw();
    EndMode2D();

    this->_screen_space.draw();

    if (this->_show_fps) {
        DrawFPS(GetScreenWidth() - 95, 10);
    }

    EndDrawing();
}

void GraphicsComponentManager::exit() { CloseWindow(); }

void GraphicsComponentManager::register_component_on_space(utils::Handle<GraphicsComponent> graphics_component) {
    // NOTE: This should be refactored if more rendering modes are added
    if (graphics_component->get_rendering_mode() == RenderingMode::SCREEN_SPACE) {
        this->_screen_space.add_component(graphics_component);
    } else {
        this->_world2D_space.add_component(graphics_component);
    }
}

void GraphicsComponentManager::unregister_component_on_space(utils::Handle<GraphicsComponent> graphics_component) {
    // NOTE: This should be refactored if more rendering modes are added
    if (graphics_component->get_rendering_mode() == RenderingMode::SCREEN_SPACE) {
        this->_screen_space.remove_component(graphics_component);
    } else {
        this->_world2D_space.remove_component(graphics_component);
    }
}
