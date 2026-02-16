#pragma once

#include <memory>

#include "components/component.hpp"
#include "containers/vector_container.hpp"
#include "utils/id.hpp"

using utils::Handle;
using utils::Identified;

class HeapAllocatedComponentContainer : public VectorContainer<std::unique_ptr<Component>> {
   public:
    HeapAllocatedComponentContainer() : VectorContainer<std::unique_ptr<Component>>() {}

    ~HeapAllocatedComponentContainer() override = default;

   protected:
    template <typename ComponentType, typename... Args>
    Handle<ComponentType> create_component(Handle<Entity> entity, Args &&...args) {
        std::unique_ptr<ComponentType> component = std::make_unique<ComponentType>(entity, std::forward<Args>(args)...);
        Handle<ComponentType> handle = static_cast<Identified *>(component.get())->make_handle<ComponentType>();

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
