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
    ComponentType *create_component(Entity *entity, Args &&...args) {
        std::unique_ptr<ComponentType> component = std::make_unique<ComponentType>(entity, std::forward<Args>(args)...);
        ComponentType *component_ptr = component.get();

        this->push_back(std::move(component));

        return component_ptr;
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

   public:
    BehaviorComponentContainer() : HeapAllocatedComponentContainer() {}
};
