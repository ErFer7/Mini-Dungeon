#pragma once

#include <utility>

#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"
#include "utils/id/identifiable.hpp"

using utils::ActivityState;
using utils::Event;
using utils::Handle;
using utils::Identified;
using utils::log_info;

class Component : public Identified {
    friend class Entity;

   public:
    typedef Event<Handle<Component>> OnDestroyEvent;
    typedef OnDestroyEvent::Listener OnDestroyListener;

   public:
    Component(Handle<Entity> entity);

    Component(Component &&other) noexcept : Identified(std::move(other)) { this->_move(std::move(other)); }

    inline Component &operator=(Component &&other) noexcept {
        Identified::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    ~Component() override = default;

    inline Handle<Entity> get_entity() const { return this->_entity; }

    inline Handle<Event<Handle<Component>>> get_on_destroy_event() {
        return this->_on_destroy_event.make_handle<Event<Handle<Component>>>();
    }

    inline Handle<ActivityState> get_activity_state() { return this->_activity_state.make_handle<ActivityState>(); }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() const { return this->_activity_state.is_active(); }

    virtual void debug_draw() = 0;

   private:
    void _move(Component &&other);

   private:
    Handle<Entity> _entity;
    OnDestroyEvent _on_destroy_event;
    ActivityState _activity_state;
};
