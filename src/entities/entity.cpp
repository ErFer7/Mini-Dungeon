#include "entities/entity.hpp"

#include <math.h>

#include <cassert>
#include <memory>
#include <vector>

#include "components/component.hpp"
#include "game_core.hpp"
#include "utils/id.hpp"

Entity::Entity() : utils::Identified(static_cast<void *>(this)) {
    this->_components = std::make_unique<ComponentsVector>();
}

Entity::~Entity() { this->destroy_all_components(); }

template <typename ComponentType>
void Entity::destroy_component() {
    int index = this->_get_component_index<ComponentType>();
    utils::Handle<Component> component = this->_components->at(index);

    component->get_on_destroy_event()->invoke(component);

    auto *component_container = GameCore::get_component_container<ComponentType>();

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

utils::Handle<Component> Entity::_get_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return component;
        }
    }

    return utils::Handle<Component>();
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
