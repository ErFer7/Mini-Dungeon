#pragma once

#include <memory>

#include "components/component.hpp"
#include "containers/vector_container.hpp"

class HeapAllocatedComponentContainer : public VectorContainer<std::unique_ptr<Component>> {
   public:
    HeapAllocatedComponentContainer() : VectorContainer<std::unique_ptr<Component>>() {}

    ~HeapAllocatedComponentContainer() override = default;

   protected:
    template <typename ComponentType, typename... Args>
    utils::Handle<ComponentType> *create_component(Entity *entity, Args &&...args) {
        std::unique_ptr<ComponentType> component = std::make_unique<ComponentType>(entity, std::forward<Args>(args)...);
        utils::Id component_id = static_cast<utils::Identified *>(component)->get_id();
        utils::Handle<ComponentType> handle = utils::Handle<ComponentType>(component_id);

        this->push_back(std::move(component));

        return handle;
    }

    template <typename ComponentType>
    inline void destroy_component(ComponentType *component) {
        this->remove(component);
    }
};

class BehaviorComponentContainer final : public HeapAllocatedComponentContainer {
    friend class Entity;
    friend class BehaviorComponentManager;
    friend class BehaviorComponent;
};
