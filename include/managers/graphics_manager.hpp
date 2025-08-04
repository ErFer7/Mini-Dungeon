#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../types.hpp"
#include "component_manager.hpp"
#include "raylib.h"

// TODO: Quad tree

enum class SortingMode { NONE, TOP_TO_DOWN, ISOMETRIC };

// TODO: Move this to a separate file
class Space {
   public:
    Space() : _sorting_mode(SortingMode::NONE) { this->_components = std::make_unique<std::vector<Graphics2DComponent *>>(); }

    Space(const Space &other) { this->_copy(other); }

    Space(Space &&other) { this->_move(std::move(other)); }

    ~Space() = default;

    Space &operator=(const Space &other) noexcept {
        this->_copy(other);

        return *this;
    }

    inline SortingMode get_sorting_mode() const { return this->_sorting_mode; }

    inline void set_sorting_mode(SortingMode sorting_mode) { this->_sorting_mode = sorting_mode; }

    void add_component(Graphics2DComponent *component);

    void remove_component(Graphics2DComponent *component);

    void sort();

    void draw();

   private:
    inline void _move(Space &&other) {
        this->_components.reset();
        this->_components = std::move(other._components);
    }

    inline void _copy(const Space &other) {
        this->_components.reset();
        this->_components = std::make_unique<std::vector<Graphics2DComponent *>>(*other._components);
    }

   private:
    SortingMode _sorting_mode;

    std::unique_ptr<std::vector<Graphics2DComponent *>> _components;
};

class GraphicsManager : public ComponentManager {
    friend class Graphics2DComponent;

   public:
    GraphicsManager(EngineCore *engine_core,
                    int screen_width,
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

    inline SortingMode get_world2d_space_sorting_mode() const { return this->_world2D_space.get_sorting_mode(); }

    inline void set_world2d_space_sorting_mode(SortingMode sorting_mode) { this->_world2D_space.set_sorting_mode(sorting_mode); }

    inline SortingMode get_screen_space_sorting_mode() const { return this->_screen_space.get_sorting_mode(); }

    inline void set_screen_space_sorting_mode(SortingMode sorting_mode) { this->_screen_space.set_sorting_mode(sorting_mode); }

   protected:
    void register_component(Component *component) override;

    void unregister_component(Component *component) override;

   private:
    // TODO: Implement set methods for all of these
    int _screen_width;
    int _screen_height;
    std::string _title;
    bool _resizable;
    bool _fullscreen;
    bool _show_fps;
    int _target_fps;
    Camera2D _camera2D;
    Space _screen_space;
    Space _world2D_space;
};