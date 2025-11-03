#include "containers/component_containers/heap_allocated_component_container.hpp"

#include <memory>

template <typename ComponentType, typename... Args>
ComponentType *HeapAllocatedComponentContainer::create_component(Entity *entity, Args &&...args) {
    std::unique_ptr<ComponentType> component = this->create_unique<ComponentType>(entity, std::forward<Args>(args)...);
    ComponentType *component_ptr = component.get();

    this->push_back(std::move(component));

    return component_ptr;
}
