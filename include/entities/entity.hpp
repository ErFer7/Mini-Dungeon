#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include <vector>

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"
#include "../utils/event.hpp"
#include "../utils/restricted_instance.hpp"

// TODO: Implement an activity state
// TODO: Implement name with a hash map
// TODO: Implement has_child for instance, type and name
// TODO: Optimize component creation
// TODO: Event listeners

class Entity : public EngineCoreDependencyInjector, RestrictedInstance {
    friend class EntityContainer;

   public:
    typedef std::vector<std::unique_ptr<Entity>> ChildrenVector;
    typedef std::vector<std::unique_ptr<Component>> ComponentsVector;

   public:
    Entity(EngineCore *engine_core, Entity *parent);

    virtual ~Entity() override;

    inline Entity *get_parent() const { return this->_parent; }

    inline Event<Entity *> &get_on_destroy_event() { return this->_on_destroy_event; }

    inline Event<Entity *> &get_on_child_create_event() { return this->_on_child_create_event; }

    inline Event<Entity *> &get_on_child_destroy_event() { return this->_on_child_destroy_event; }

    inline Event<Entity *, Component *> &get_on_component_create_event() { return this->_on_component_create_event; }

    inline Event<Entity *, Component *> &get_on_component_destroy_event() { return this->_on_component_destroy_event; }

    template <typename T, typename... Args>
    T *create_child(Args &&...args) {
        this->_children->push_back(this->create_unique<T>(this, std::forward<Args>(args)...));

        Entity *child = this->_children->back().get();
        this->_on_child_create_event.invoke(child);

        return static_cast<T *>(child);
    }

    inline Entity *get_child(unsigned int index) const { return this->_children->at(index).get(); }

    int get_child_index(Entity *entity) const;

    inline unsigned int get_child_count() const { return this->_children->size(); }

    void destroy_child(unsigned int index);

    void destroy_all_children();

    void destroy();

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
    Entity *_parent;
    std::unique_ptr<ChildrenVector> _children;
    std::unique_ptr<ComponentsVector> _components;
    Event<Entity *> _on_destroy_event;
    Event<Entity *> _on_child_create_event;
    Event<Entity *> _on_child_destroy_event;
    Event<Entity *, Component *> _on_component_create_event;
    Event<Entity *, Component *> _on_component_destroy_event;
};
