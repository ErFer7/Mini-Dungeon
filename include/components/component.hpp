#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/game_core_dependency_injector.hpp"
#include "../utils/restricted_instance.hpp"

// TODO: Implement an activity state

using utils::Event;
using utils::GameCoreDependencyInjector;
using utils::RestrictedInstance;

class Component : public GameCoreDependencyInjector, RestrictedInstance {
    friend class Entity;

   public:
    Component(GameCore *game_core, Entity *entity) : GameCoreDependencyInjector(game_core), _entity(entity) {}

    inline Entity *get_entity() const { return this->_entity; }

    inline Event<Component *> *get_on_destroy_event() { return &this->_on_destroy_event; }

   protected:
    virtual void register_component() = 0;

    virtual void unregister_component() = 0;

   private:
    Entity *_entity;
    Event<Component *> _on_destroy_event;
};
