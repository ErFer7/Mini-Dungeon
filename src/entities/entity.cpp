#include "entities/entity.hpp"

#include <math.h>

#include <cassert>
#include <memory>
#include <typeindex>

#include "components/component.hpp"
#include "game_core.hpp"

Entity::Entity() : utils::Identified(static_cast<void *>(this)) {
    this->_components = std::make_unique<ComponentsMap>();
}

Entity::~Entity() { this->destroy_all_components(); }

template <typename ComponentType>
void Entity::destroy_component() {
    std::type_index type_index = static_cast<std::type_index>(typeid(ComponentType));
    Handle<Component> component = this->_components->at(type_index);

    component->get_on_destroy_event()->invoke(component);

    auto *component_container = GameCore::get_component_container<ComponentType>();

    component_container->template destroy_component<ComponentType>(component);
    this->_components->erase(type_index);
}

void Entity::destroy_all_components() {
    for (auto &[_, component] : *this->_components) {
        if (!component.is_null()) {
            component->get_on_destroy_event()->invoke(component);
        }
    }

    this->_components->clear();
}

void Entity::_move(Entity &&other) {
    if (this == &other) {
        return;
    }

    this->update_reference(this);

    this->_components = std::move(other._components);
    this->_on_destroy_event = std::move(other._on_destroy_event);
    this->_activity_state = std::move(other._activity_state);
}
