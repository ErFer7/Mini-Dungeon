#pragma once

#include <utility>

#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"
#include "utils/restricted_instance.hpp"
#include "utils/uncopiable.hpp"

using std::forward;
using utils::ActivityState;
using utils::Event;
using utils::log_info;
using utils::RestrictedInstance;

class Component : public utils::Uncopiable {
    friend class Entity;

   public:
    typedef Event<Component *> OnDestroyEvent;
    typedef OnDestroyEvent::Listener OnDestroyListener;

   public:
    Component(Entity *entity);

    inline Entity *get_entity() const { return this->_entity; }

    inline Event<Component *> *get_on_destroy_event() { return &this->_on_destroy_event; }

    inline ActivityState *get_activity_state() { return &this->_activity_state; }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() { return this->_activity_state.is_active(); }

   private:
    Entity *_entity;
    OnDestroyEvent _on_destroy_event;
    ActivityState _activity_state;
};
