#include "managers/graphics_component_manager.hpp"

#include "components/graphics_component.hpp"

// FIX: This is really outdated
// NOTE: STOPPED HERE LAST TIME (2026-02-02)
using std::remove;

void Space::add_component(GraphicsComponent *component) { this->_components->push_back(component); }

void Space::remove_component(GraphicsComponent *component) {
    this->_components->erase(remove(this->_components->begin(), this->_components->end(), component),
                             this->_components->end());
}

void Space::sort() {
    switch (this->_sorting_mode) {
        case SortingMode::NONE:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](GraphicsComponent *comp_a, GraphicsComponent *comp_b) -> bool {
                          if (comp_a == nullptr) {
                              return true;
                          } else if (comp_b == nullptr) {
                              return false;
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        case SortingMode::TOP_TO_DOWN:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](GraphicsComponent *comp_a, GraphicsComponent *comp_b) -> bool {
                          if (comp_a == nullptr) {
                              return true;
                          } else if (comp_b == nullptr) {
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
                      [](GraphicsComponent *comp_a, GraphicsComponent *comp_b) -> bool {
                          if (comp_a == nullptr) {
                              return true;
                          } else if (comp_b == nullptr) {
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

GraphicsComponentManager::GraphicsComponentManager(GameCore *game_core,
                                                   int screen_width,
                                                   int screen_height,
                                                   const char *title,
                                                   int target_fps,
                                                   bool resizable,
                                                   bool fullscreen,
                                                   bool show_fps)
    : ComponentManager(game_core) {
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

void GraphicsComponentManager::register_component(Component *component) {
    ComponentManager::register_component(component);

    GraphicsComponent *graphics2D_component = static_cast<GraphicsComponent *>(component);
    RenderingMode rendering_mode = graphics2D_component->get_rendering_mode();

    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        this->_world2D_space.add_component(graphics2D_component);
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        this->_screen_space.add_component(graphics2D_component);
    }
}

void GraphicsComponentManager::unregister_component(Component *component) {
    GraphicsComponent *graphics2D_component = static_cast<GraphicsComponent *>(component);

    RenderingMode rendering_mode = graphics2D_component->get_rendering_mode();

    if (rendering_mode == RenderingMode::WORLD_SPACE_2D) {
        this->_world2D_space.remove_component(graphics2D_component);
    } else if (rendering_mode == RenderingMode::SCREEN_SPACE) {
        this->_screen_space.remove_component(graphics2D_component);
    }
}

template <typename ComponentType, typename... Args>
ComponentType *GraphicsComponentManager::create_component(Entity *entity, Args &&...args) {
    this->_behavior_components->push_back(this->create_unique<ComponentType>(std::forward<Args>(args)...));

    return this->_behavior_components->back().get();  // TODO: Avoid end()
};

void GraphicsComponentManager::destroy_component(BehaviorComponent *component) {
    this->_behavior_components->erase(std::find(this->_behavior_components->begin(),
                                                this->_behavior_components->end(),
                                                std::unique_ptr<BehaviorComponent>(component)));
};
