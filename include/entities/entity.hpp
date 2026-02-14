#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "components/component.hpp"
#include "game_core.hpp"
#include "types.hpp"
#include "utils/activity_state.hpp"
#include "utils/event.hpp"
#include "utils/id.hpp"

// TODO: Implement name with a hash map
// TODO: Optimize component creation
// TODO: Event listeners

using std::forward;
using std::type_info;
using std::unique_ptr;
using std::vector;
using utils::ActivityState;
using utils::Event;

class Entity : public utils::Identified {
    friend class EntityContainer;

   public:
    typedef vector<utils::Handle<Component>> ComponentsVector;

   public:
    Entity();

    Entity(Entity &&other) : utils::Identified(std::move(other)) { this->_move(std::move(other)); }

    virtual ~Entity() override;

    Entity &operator=(Entity &&other) {
        utils::Identified::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Event<utils::Handle<Entity>> &get_on_destroy_event() { return this->_on_destroy_event; }

    template <typename ComponentType, typename... Args>
    utils::Handle<ComponentType> create_component(Args &&...args) {
        auto *component_container = GameCore::get_instance()->get_component_container<ComponentType>();

        this->_components->push_back(
            component_container->template create_component<ComponentType>(this, forward<Args>(args)...));

        // TODO: Refactor to avoid getting the back
        return static_cast<utils::Handle<ComponentType>>(this->_components->back());
    }

    inline unsigned int get_component_count() const { return this->_components->size(); }

    void destroy_component(unsigned int index);

    void destroy_all_components();

    template <typename ComponentType>
    bool has_component() const;

    template <typename ComponentType>
    inline utils::Handle<ComponentType> get_component() const {
        return static_cast<utils::Handle<ComponentType>>(this->_get_component(typeid(ComponentType)));
    }

    template <typename ComponentType>
    void destroy_component();

    inline utils::Handle<ActivityState> get_activity_state() {
        return utils::Handle<ActivityState>(this->_activity_state.get_id());
    }

    inline void set_active(bool is_active) { this->_activity_state.set_active(is_active); }

    inline bool is_active() { return this->_activity_state.is_active(); }

   protected:
    inline void set_activity_state_parent(utils::Handle<ActivityState> activity_state) {
        this->_activity_state.set_parent_activity_state(activity_state);
    }

   private:
    void _move(Entity &&other) {
        if (this == &other) {
            return;
        }

        this->update_reference(this);

        this->_components = std::move(other._components);
        this->_on_destroy_event = std::move(other._on_destroy_event);
        this->_activity_state = std::move(other._activity_state);
    }

    utils::Handle<Component> _get_component(const type_info &type_info) const;

    template <typename ComponentType>
    int _get_component_index() const;

   private:
    unique_ptr<ComponentsVector> _components;
    Event<utils::Handle<Entity>> _on_destroy_event;
    ActivityState _activity_state;
};
