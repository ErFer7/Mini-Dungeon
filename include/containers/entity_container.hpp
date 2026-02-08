#pragma once

#include <memory>
#include <utility>

#include "containers/vector_container.hpp"
#include "entities/entity.hpp"
#include "types.hpp"

class EntityContainer : public VectorContainer<std::unique_ptr<Entity>> {
   public:
    EntityContainer() : VectorContainer<std::unique_ptr<Entity>>() {}

    ~EntityContainer() override = default;

    template <typename EntityType, typename... Args>
    EntityType *create_entity(Args &&...args) {
        std::unique_ptr<EntityType> entity_unique_ptr = std::make_unique<EntityType>(std::forward<Args>(args)...);
        EntityType *entity = entity_unique_ptr.get();

        this->push_back(std::move(entity_unique_ptr));

        return entity;
    }

    inline Entity *get_entity(unsigned int index) const { return this->get_ref(index)->get(); }

    inline size_t get_entity_count() const { return this->size(); }

    void destroy_entity(unsigned int index);

    void destroy_entity(Entity *entity);

    void destroy_all_entities();
};
