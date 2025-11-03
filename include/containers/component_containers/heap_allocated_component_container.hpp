#pragma once

#include <memory>

#include "components/component.hpp"
#include "containers/vector_container.hpp"

class HeapAllocatedComponentContainer : public VectorContainer<std::unique_ptr<Component>> {
   public:
    HeapAllocatedComponentContainer() = default;

    HeapAllocatedComponentContainer(GameCore *game_core) : VectorContainer<std::unique_ptr<Component>>(game_core) {}

    ~HeapAllocatedComponentContainer() override = default;

   protected:
    template <typename ComponentType, typename... Args>
    ComponentType *create_component(Entity *entity, Args &&...args);

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
