#pragma once

#include <raylib.h>

#include <string>

#include "components/graphics_component.hpp"
#include "managers/graphics/graphical_debugging_manager.hpp"
#include "managers/graphics/graphics_enums.hpp"
#include "managers/graphics/space.hpp"
#include "managers/manager.hpp"
#include "utils/event.hpp"
#include "utils/id/handle.hpp"

using utils::Handle;

class GraphicsManager final : public Manager {
    friend class GraphicsComponent;

   public:
    typedef Event<int, int> ScreenResizeEvent;
    typedef ScreenResizeEvent::Listener ScreenResizeListener;

   public:
    GraphicsManager() = default;

    GraphicsManager(int screen_width,
                    int screen_height,
                    const char *title,
                    int target_fps = 60,
                    bool resizable = false,
                    bool fullscreen = false,
                    bool show_fps = false);

    ~GraphicsManager() override = default;

    void init() override;

    void update() override;

    void exit() override;

    inline int get_screen_width() const { return this->_screen_width; }

    inline int get_screen_height() const { return this->_screen_height; }

    inline std::string get_title() const { return this->_title; }

    inline bool is_resizable() const { return this->_resizable; }

    inline bool is_fullscreen() const { return this->_fullscreen; }

    inline bool is_showing_fps() const { return this->_show_fps; }

    inline int get_target_fps() const { return this->_target_fps; }

    inline Camera2D get_camera2D() const { return this->_camera2D; }

    inline void set_camera_position(Vector2Df position) { this->_camera2D.target = Vector2{position.x, -position.y}; }

    inline SortingMode get_world_space2D_sorting_mode() const { return this->_world_space2D.get_sorting_mode(); }

    inline void set_world_space2D_sorting_mode(SortingMode sorting_mode) {
        this->_world_space2D.set_sorting_mode(sorting_mode);
    }

    inline SortingMode get_screen_space_sorting_mode() const { return this->_screen_space.get_sorting_mode(); }

    inline void set_screen_space_sorting_mode(SortingMode sorting_mode) {
        this->_screen_space.set_sorting_mode(sorting_mode);
    }

    inline Handle<ScreenResizeEvent> get_on_screen_resize_event() {
        return this->_on_screen_resize.make_handle<ScreenResizeEvent>();
    }

    void register_component_on_space(Handle<GraphicsComponent> graphics_component);

    void unregister_component_on_space(Handle<GraphicsComponent> graphics_component);

   private:
    // TODO: Implement set methods for all of these
    int _screen_width;
    int _screen_height;
    std::string _title;
    bool _resizable;
    bool _fullscreen;
    bool _show_fps;
    int _target_fps;
    Camera2D _camera2D;  // TODO: Fix pixel perfect camera
    Space _screen_space;
    Space _world_space2D;
    ScreenResizeEvent _on_screen_resize;
    GraphicalDebuggingManager _graphical_debugging_manager;  // Submanager
};
