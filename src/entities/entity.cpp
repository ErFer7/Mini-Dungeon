#include "../../include/entities/entity.hpp"

#include <math.h>

#include <cassert>
#include <cstddef>
#include <memory>
#include <vector>

#include "../../include/components/component.hpp"

Entity::Entity(GameCore *game_core) : GameCoreDependencyInjector(game_core) { this->_components = std::make_unique<ComponentsVector>(); }

Entity::~Entity() { this->destroy_all_components(); }

Component *Entity::get_component(unsigned int index) const { return this->_components->at(index).get(); }

int Entity::get_component_index(Component *component) const {
    for (size_t i = 0; i < this->_components->size(); i++) {
        if (this->_components->at(i).get() == component) {
            return i;
        }
    }

    return -1;
}

void Entity::destroy_component(unsigned int index) {
    Component *component = this->_components->at(index).get();
    component->get_on_destroy_event()->invoke(component);
    component->unregister_component();
    this->_components->erase(this->_components->begin() + index);
}

void Entity::destroy_all_components() {
    for (auto &component : *this->_components) {
        component->get_on_destroy_event()->invoke(component.get());
        component->unregister_component();
    }

    this->_components->clear();
}

Component *Entity::_register_created_component(std::unique_ptr<Component> component) {
    if (!this->_has_component(typeid(*component))) {
        this->_components->push_back(std::move(component));

        Component *component_raw_ref = this->_components->back().get();

        component_raw_ref->register_component();

        return component_raw_ref;
    }

    return nullptr;  // TODO: Throw an exception here
}

bool Entity::_has_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return true;
        }
    }

    return false;
}

Component *Entity::_get_component(const std::type_info &type_info) const {
    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return component.get();
        }
    }

    return nullptr;
}

int Entity::_get_component_index(const std::type_info &type_info) const {
    unsigned int index = 0;

    for (auto &component : *this->_components) {
        if (typeid(*component) == type_info) {
            return index;
        }

        index++;
    }

    return -1;
}

void Entity::_destroy_component(const std::type_info &type_info) {
    unsigned int index = this->_get_component_index(type_info);
    this->destroy_component(index);
}
