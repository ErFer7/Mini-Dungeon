#include "../../include/containers/entity_container.hpp"

#include <cassert>
#include <memory>

#include "../../include/entities/entity.hpp"

using std::make_unique;

EntityContainer::EntityContainer(GameCore *game_core) : Container(game_core) { this->_entities = make_unique<EntityVector>(); }

int EntityContainer::get_entity_index(Entity *entity) const {
    for (size_t i = 0; i < this->_entities->size(); i++) {
        if (this->_entities->at(i).get() == entity) {
            return i;
        }
    }

    return -1;
}

void EntityContainer::destroy_entity(unsigned int index) {
    Entity *entity = this->_entities->at(index).get();

    entity->get_on_destroy_event().invoke(entity);
    this->_entities->erase(this->_entities->begin() + index);
}

void EntityContainer::destroy_entity(Entity *entity) {
    int index = this->get_entity_index(entity);

    if (index >= 0) {
        this->destroy_entity(index);
    }
};

void EntityContainer::destroy_all_entities() {
    assert(this->_entities != nullptr);

    for (auto it = this->_entities->begin(); it != this->_entities->end(); ++it) {
        Entity *entity = it->get();
        entity->get_on_destroy_event().invoke(entity);
    }

    this->_entities->clear();
}

void EntityContainer::free() { this->destroy_all_entities(); }
