#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/game_core_dependency_injector.hpp"
#include "../utils/restricted_instance.hpp"

// TODO: Implement an activity state
// TODO: Implement name with a hash map
// TODO: Optimize component creation
// TODO: Event listeners

using utils::Event;
using utils::GameCoreDependencyInjector;
using utils::RestrictedInstance;

class Entity : public GameCoreDependencyInjector, RestrictedInstance {
    friend class EntityContainer;

   public:
    typedef std::vector<std::unique_ptr<Component>> ComponentsVector;

   public:
    Entity(GameCore *game_core, Entity *parent);

    virtual ~Entity() override;

    inline Event<Entity *> &get_on_destroy_event() { return this->_on_destroy_event; }

    template <typename T, typename... Args>
    T *create_component(Args &&...args) {
        return static_cast<T *>(this->_register_created_component(this->create_unique<T>(this, std::forward<Args>(args)...)));
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

   private:
    Component *_register_created_component(std::unique_ptr<Component> component);

    bool _has_component(const std::type_info &type_info) const;

    Component *_get_component(const std::type_info &type_info) const;

    int _get_component_index(const std::type_info &type_info) const;

    void _destroy_component(const std::type_info &type_info);

   private:
    std::unique_ptr<ComponentsVector> _components;
    Event<Entity *> _on_destroy_event;
};
