#pragma once

#include <utility>

#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"
#include "utils/id.hpp"

using std::forward;
using utils::ActivityState;
using utils::Event;
using utils::log_info;

class Component : public utils::Identified {
    friend class Entity;

   public:
    typedef Event<utils::Handle<Component>> OnDestroyEvent;
    typedef OnDestroyEvent::Listener OnDestroyListener;

   public:
    Component(Entity *entity);

    Component(Component &&other) : utils::Identified(std::move(other)) { this->_move(std::move(other)); };

    Component &operator=(Component &&other) noexcept {
        utils::Identified::operator=(std::move(other));
        this->_move(std::move(other));
        return *this;
    };

    ~Component() override = default;

    inline Entity *get_entity() const { return this->_entity; }

    inline Event<utils::Handle<Component>> *get_on_destroy_event() { return &this->_on_destroy_event; }

    inline ActivityState *get_activity_state() { return &this->_activity_state; }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() { return this->_activity_state.is_active(); }

   private:
    void _move(Component &&other) {
        this->_entity = other.get_entity();
        this->_on_destroy_event = std::move(other._on_destroy_event);
        this->_activity_state = std::move(other._activity_state);

        this->update_reference(this);
    }

   private:
    Entity *_entity;
    OnDestroyEvent _on_destroy_event;
    ActivityState _activity_state;
};
