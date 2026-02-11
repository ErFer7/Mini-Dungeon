#include "containers/entity_container.hpp"

#include <cassert>
#include <memory>

#include "entities/entity.hpp"
#include "utils/id.hpp"

void EntityContainer::destroy_entity(unsigned int index) {
    Entity *entity = this->get_ref(index)->get();

    entity->get_on_destroy_event().invoke(utils::Handle<Entity>(static_cast<utils::Identified *>(entity)->get_id()));
    this->remove(index);
}

void EntityContainer::destroy_entity(utils::Handle<Entity> entity) {
    entity->get_on_destroy_event().invoke(entity);
    this->remove(std::unique_ptr<Entity>(entity.get_pointer()));
};

void EntityContainer::destroy_all_entities() {
    for (auto &entity : *this->get_data_structure()) {
        entity->get_on_destroy_event().invoke(
            utils::Handle<Entity>(static_cast<utils::Identified *>(entity.get())->get_id()));
    }

    this->free();
}
