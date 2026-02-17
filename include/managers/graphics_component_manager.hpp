#pragma once

#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "components/graphics_component.hpp"
#include "managers/manager.hpp"
#include "utils/id.hpp"

using utils::Handle;

// TODO: Quad tree

enum class RenderingMode { SCREEN_SPACE, WORLD_SPACE_2D };
enum class SortingMode { NONE, TOP_TO_DOWN, ISOMETRIC };

// TODO: Move this to a separate file
class Space {
   public:
    typedef std::vector<Handle<GraphicsComponent>> GraphicsComponentVector;

   public:
    Space() : _sorting_mode(SortingMode::NONE) { this->_components = std::make_unique<GraphicsComponentVector>(); }

    // TODO: Check if this is necessary
    Space(const Space &other) { this->_copy(other); }

    // TODO: Check if this is necessary
    Space(Space &&other) { this->_move(std::move(other)); }

    ~Space() = default;

    // TODO: Check if this is necessary
    Space &operator=(Space &other) {
        this->_copy(other);

        return *this;
    }

    // TODO: Check if this is necessary
    Space &operator=(Space &&other) {
        this->_move(std::move(other));

        return *this;
    }

    inline SortingMode get_sorting_mode() const { return this->_sorting_mode; }

    inline void set_sorting_mode(SortingMode sorting_mode) { this->_sorting_mode = sorting_mode; }

    void add_component(Handle<GraphicsComponent> component);

    void remove_component(Handle<GraphicsComponent> component);

    void sort();

    void draw();

   private:
    // TODO: Check if this is necessary
    inline void _move(Space &&other) {
        this->_components.reset();
        this->_components = std::move(other._components);
    }

    // TODO: Check if this is necessary
    inline void _copy(const Space &other) {
        this->_components.reset();
        this->_components = std::make_unique<GraphicsComponentVector>(*other._components);
    }

   private:
    SortingMode _sorting_mode;
    std::unique_ptr<GraphicsComponentVector> _components;
};

class GraphicsComponentManager : public Manager {
    friend class GraphicsComponent;

   public:
    GraphicsComponentManager() = default;

    GraphicsComponentManager(int screen_width,
                             int screen_height,
                             const char *title,
                             int target_fps = 60,
                             bool resizable = false,
                             bool fullscreen = false,
                             bool show_fps = false);

    ~GraphicsComponentManager() override = default;

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

    inline SortingMode get_world_space2D_sorting_mode() const { return this->_world_space2D.get_sorting_mode(); }

    inline void set_world_space_sorting_mode(SortingMode sorting_mode) {
        this->_world_space2D.set_sorting_mode(sorting_mode);
    }

    inline SortingMode get_screen_space_sorting_mode() const { return this->_screen_space.get_sorting_mode(); }

    inline void set_screen_space_sorting_mode(SortingMode sorting_mode) {
        this->_screen_space.set_sorting_mode(sorting_mode);
    }

    void debug_draw_rectangle(Rectangle rectangle, Vector2Df position, float rotation, Color color);

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
};
