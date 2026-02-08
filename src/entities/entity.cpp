#include "entities/entity.hpp"

#include <math.h>

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "components/component.hpp"
#include "game_core.hpp"

using std::forward;
using std::make_unique;
using std::move;
using std::type_info;
using std::unique_ptr;

Entity::Entity() { this->_components = make_unique<ComponentsVector>(); }

Entity::~Entity() { this->destroy_all_components(); }

template <typename ComponentType, typename... Args>
ComponentType *Entity::create_component(Args &&...args) {
    auto *component_container = GameCore::get_instance()->get_component_container<ComponentType>();

    this->_components->push_back(
        component_container->template create_component<ComponentType>(this, forward<Args>(args)...));

    // TODO: Refactor to avoid getting the back
    return this->_components->back();
}

template <typename ComponentType>
void Entity::destroy_component() {
    int index = this->_get_component_index<ComponentType>();
    Component *component = this->_components->at(index);

    component->get_on_destroy_event()->invoke(component);

    auto *component_container = GameCore::get_instance()->get_component_container<ComponentType>();

    component_container->template destroy_component<ComponentType>(component);
    this->_components->erase(this->_components->begin() + index);
}

void Entity::destroy_all_components() {
    for (auto &component : *this->_components) {
        component->get_on_destroy_event()->invoke(component);
    }

    this->_components->clear();
}

template <typename ComponentType>
inline bool Entity::has_component() const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == typeid(ComponentType)) {
            return true;
        }
    }

    return false;
}

Component *Entity::_get_component(const type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return component;
        }
    }

    return nullptr;
}

template <typename ComponentType>
int Entity::_get_component_index() const {
    unsigned int index = 0;

    for (auto &component : *this->_components) {
        if (typeid(*component) == typeid(ComponentType)) {
            return index;
        }

        index++;
    }

    return -1;
}
