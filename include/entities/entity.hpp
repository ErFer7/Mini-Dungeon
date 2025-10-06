#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../types.hpp"
#include "../utils/activity_state.hpp"
#include "../utils/event.hpp"
#include "../utils/game_core_dependency_injector.hpp"
#include "../utils/restricted_instance.hpp"
#include "components/component.hpp"

// TODO: Implement an activity state
// TODO: Implement name with a hash map
// TODO: Optimize component creation
// TODO: Event listeners

using std::forward;
using std::type_info;
using std::unique_ptr;
using std::vector;
using utils::ActivityState;
using utils::Event;
using utils::GameCoreDependencyInjector;
using utils::RestrictedInstance;

class Entity : public GameCoreDependencyInjector, RestrictedInstance {
    friend class EntityContainer;

   public:
    typedef vector<unique_ptr<Component>> ComponentsVector;

   public:
    Entity(GameCore *game_core);

    virtual ~Entity() override;

    inline Event<Entity *> &get_on_destroy_event() { return this->_on_destroy_event; }

    template <typename T, typename... Args>
    T *create_component(Args &&...args) {
        return static_cast<T *>(this->_register_created_component(this->create_unique<T>(this, forward<Args>(args)...)));
    }

    Component *get_component(unsigned int index) const;

    int get_component_index(Component *component) const;

    inline unsigned int get_component_count() const { return this->_components->size(); }

    void destroy_component(unsigned int index);

    void destroy_all_components();

    template <typename T>
    inline bool has_component() const {
        return this->_has_component(typeid(T));
    }

    template <typename T>
    inline T *get_component() const {
        return static_cast<T *>(this->_get_component(typeid(T)));
    }

    template <typename T>
    inline int get_component_index() const {
        return this->_get_component_index(typeid(T));
    }

    template <typename T>
    inline void destroy_component() {
        this->_destroy_component(typeid(T));
    }

    inline ActivityState *get_activity_state() { return &this->_activity_state; }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() { return this->_activity_state.is_active(); }

   private:
    Component *_register_created_component(unique_ptr<Component> component);

    bool _has_component(const type_info &type_info) const;

    Component *_get_component(const type_info &type_info) const;

    int _get_component_index(const type_info &type_info) const;

    void _destroy_component(const type_info &type_info);

   private:
    unique_ptr<ComponentsVector> _components;
    Event<Entity *> _on_destroy_event;
    ActivityState _activity_state;
};
