#pragma once

#include <memory>
#include <utility>

#include "containers/vector_container.hpp"
#include "entities/entity.hpp"
#include "types.hpp"

using utils::Handle;
using utils::Identified;

class EntityContainer : public VectorContainer<std::unique_ptr<Entity>> {
   public:
    EntityContainer() : VectorContainer<std::unique_ptr<Entity>>() {}

    ~EntityContainer() override = default;

    template <typename EntityType, typename... Args>
    Handle<EntityType> create_entity(Args &&...args) {
        std::unique_ptr<EntityType> entity = std::make_unique<EntityType>(std::forward<Args>(args)...);
        Handle<EntityType> handle = static_cast<Identified *>(entity.get())->make_handle<EntityType>();

        this->push_back(std::move(entity));

        return handle;
    }

    inline Entity *get_entity(unsigned int index) const { return this->get_ref(index)->get(); }

    inline size_t get_entity_count() const { return this->size(); }

    void destroy_entity(unsigned int index);

    void destroy_entity(utils::Handle<Entity> entity);

    void destroy_all_entities();
};
