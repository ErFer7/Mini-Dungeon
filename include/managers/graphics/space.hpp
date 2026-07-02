#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "managers/graphics/graphics_enums.hpp"
#include "utils/id/handle.hpp"

using utils::Handle;

// TODO: Quad tree

class Space final {
   public:
    typedef std::vector<Handle<GraphicsComponent>> GraphicsComponentVector;

   public:
    Space() : _sorting_mode(SortingMode::NONE) {
        this->_active_components = std::make_unique<GraphicsComponentVector>();
        this->_inactive_components = std::make_unique<GraphicsComponentVector>();
    }

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

    void handle_activity_update(Handle<GraphicsComponent> component);

    void sort();

    void draw();

   private:
    // TODO: Check if this is necessary
    inline void _move(Space &&other) {
        this->_active_components.reset();
        this->_active_components = std::move(other._active_components);

        this->_inactive_components.reset();
        this->_inactive_components = std::move(other._inactive_components);
    }

    // TODO: Check if this is necessary
    inline void _copy(const Space &other) {
        this->_active_components.reset();
        this->_active_components = std::make_unique<GraphicsComponentVector>(*other._active_components);

        this->_inactive_components.reset();
        this->_inactive_components = std::make_unique<GraphicsComponentVector>(*other._inactive_components);
    }

   private:
    SortingMode _sorting_mode;
    std::unique_ptr<GraphicsComponentVector> _active_components;
    std::unique_ptr<GraphicsComponentVector> _inactive_components;
};
