#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "../utils/game_core_dependency_injector.hpp"
#include "container.hpp"

using std::forward;
using std::unique_ptr;
using std::vector;
using utils::GameCoreDependencyInjector;

class EntityContainer : public Container {
   public:
    typedef vector<unique_ptr<Entity>> EntityVector;

   public:
    EntityContainer() = default;

    EntityContainer(GameCore *game_core);

    ~EntityContainer() override = default;

    template <typename T, typename... Args>
    T *create_entity(Args &&...args) {
        this->_entities->push_back(this->create_unique<T>(forward<Args>(args)...));

        Entity *entity = this->_entities->back().get();

        return static_cast<T *>(entity);
    }

    inline Entity *get_entity(unsigned int index) const { return this->_entities->at(index).get(); }

    int get_entity_index(Entity *entity) const;

    inline unsigned int get_entity_count() const { return this->_entities->size(); }

    void destroy_entity(unsigned int index);

    inline void destroy_entity(Entity *entity) { this->destroy_entity(this->get_entity_index(entity)); };

    void destroy_all_entities();

    void free() override;

   private:
    unique_ptr<EntityVector> _entities;
};
