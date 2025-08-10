#pragma once

#include <memory>
#include <utility>

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "../utils/game_core_dependency_injector.hpp"

using utils::GameCoreDependencyInjector;

class EntityContainer : public GameCoreDependencyInjector {
   public:
    typedef std::vector<std::unique_ptr<Entity>> EntityVector;

   public:
    EntityContainer() = default;

    EntityContainer(GameCore *game_core);

    ~EntityContainer();

    // TODO: Check the args
    template <typename T, typename... Args>
    T *create_entity(Args &&...args) {
        this->_entities->push_back(this->create_unique<T>(std::forward<Args>(args)...));

        Entity *entity = this->_entities->back().get();

        return static_cast<T *>(entity);
    }

    inline Entity *get_entity(unsigned int index) const { return this->_entities->at(index).get(); }

    int get_entity_index(Entity *entity) const;

    inline unsigned int get_entity_count() const { return this->_entities->size(); }

    void destroy_entity(unsigned int index);

    inline void destroy_entity(Entity *entity) { this->destroy_entity(this->get_entity_index(entity)); };

    void destroy_all_entities();

   private:
    std::unique_ptr<EntityVector> _entities;
};
