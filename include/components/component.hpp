#pragma once

#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/event.hpp"
#include "utils/game_core_dependency_injector.hpp"
#include "utils/restricted_instance.hpp"

// TODO: Implement an activity state

using utils::ActivityState;
using utils::Event;
using utils::GameCoreDependencyInjector;
using utils::RestrictedInstance;

class Component : public GameCoreDependencyInjector, RestrictedInstance {
    friend class Entity;

   public:
    Component(GameCore *game_core, Entity *entity);

    inline Entity *get_entity() const { return this->_entity; }

    inline Event<Component *> *get_on_destroy_event() { return &this->_on_destroy_event; }

    inline ActivityState *get_activity_state() { return &this->_activity_state; }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() { return this->_activity_state.is_active(); }

   protected:
    virtual void register_component() = 0;

    virtual void unregister_component() = 0;

   private:
    Entity *_entity;
    Event<Component *> _on_destroy_event;
    ActivityState _activity_state;
};
