#include "containers/entity_container.hpp"

#include <cassert>
#include <memory>

#include "entities/entity.hpp"

using std::make_unique;

void EntityContainer::destroy_entity(unsigned int index) {
    Entity *entity = this->get_ref(index)->get();

    entity->get_on_destroy_event().invoke(entity);
    this->remove(index);
}

void EntityContainer::destroy_entity(Entity *entity) {
    entity->get_on_destroy_event().invoke(entity);
    this->remove(std::unique_ptr<Entity>(entity));
};

void EntityContainer::destroy_all_entities() {
    for (auto &entity : *this->get_data_structure()) {
        entity->get_on_destroy_event().invoke(entity.get());
    }

    this->free();
}
