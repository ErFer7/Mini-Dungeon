#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "components/component.hpp"
#include "game_core.hpp"
#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"

// TODO: Implement name with a hash map
// TODO: Event listeners

using utils::ActivityState;
using utils::Event;
using utils::Handle;
using utils::Identified;
using utils::log_error;

class Entity : public Identified {
    friend class EntityContainer;

   public:
    typedef std::unordered_map<std::type_index, Handle<Component>> ComponentsMap;

   public:
    Entity();

    Entity(Entity &&other) noexcept : Identified(std::move(other)) { this->_move(std::move(other)); }

    virtual ~Entity() override;

    Entity &operator=(Entity &&other) noexcept {
        Identified::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Event<Handle<Entity>> &get_on_destroy_event() { return this->_on_destroy_event; }

    template <typename ComponentType, typename... Args>
    Handle<ComponentType> create_component(Args &&...args) {
        std::type_index type_index = static_cast<std::type_index>(typeid(ComponentType));
        if (!this->get_component<ComponentType>().is_null()) {
            log_error(this, "Entity: Atempting to add an already existing component");
            return Handle<ComponentType>();
        }

        auto *component_container = GameCore::get_component_container<ComponentType>();

        (*this->_components)[type_index] = component_container->template create_component<ComponentType>(
            this->make_handle<Entity>(), std::forward<Args>(args)...);

        return static_cast<Handle<ComponentType>>(this->_components->at(type_index));
    }

    inline unsigned int get_component_count() const { return this->_components->size(); }

    void destroy_component(unsigned int index);

    void destroy_all_components();

    template <typename ComponentType>
    inline bool has_component() const {
        return !this->get_component<ComponentType>().is_null();
    }

    template <typename ComponentType>
    inline Handle<ComponentType> get_component() const {
        return static_cast<Handle<ComponentType>>(
            (*this->_components)[static_cast<std::type_index>(typeid(ComponentType))]);
    }

    template <typename ComponentType>
    void destroy_component();

    inline Handle<ActivityState> get_activity_state() { return this->_activity_state.make_handle<ActivityState>(); }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() const { return this->_activity_state.is_active(); }

   protected:
    inline void set_activity_state_parent(Handle<ActivityState> activity_state) {
        this->_activity_state.set_parent_activity_state(activity_state);
    }

   private:
    void _move(Entity &&other);

   private:
    std::unique_ptr<ComponentsMap> _components;
    Event<Handle<Entity>> _on_destroy_event;
    ActivityState _activity_state;
};
