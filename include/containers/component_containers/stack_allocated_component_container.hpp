#pragma once

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "containers/vector_container.hpp"
#include "types.hpp"

template <typename ComponentType>
class StackAllocatedComponentContainer : public VectorContainer<ComponentType> {
   public:
    StackAllocatedComponentContainer() : VectorContainer<ComponentType>() {}

    ~StackAllocatedComponentContainer() override = default;

    // The first type parameter is declared to satisfy the calls. See the HeapAllocatedComponentContainer
    template <typename, typename... Args>
    ComponentType *create_component(Entity *entity, Args &&...args) {
        ComponentType component = this->template create<ComponentType>(entity, std::forward<Args>(args)...);
        ComponentType *component_ptr = &component;

        this->push_back(std::move(component));

        return component_ptr;
    }

    template <typename>
    inline void destroy_component(ComponentType *component) {
        this->remove(component);
    }
};

class PhysicsComponentContainer final : public StackAllocatedComponentContainer<PhysicsComponent> {
    friend class PhysicsComponentManager;

    // public:
    // PhysicsComponentContainer() : StackAllocatedComponentContainer<PhysicsComponent>() {}
};

typedef StackAllocatedComponentContainer<ColliderComponent> ColliderComponentContainer;
typedef StackAllocatedComponentContainer<GraphicsComponent> GraphicsComponentContainer;
typedef StackAllocatedComponentContainer<TextComponent> TextComponentContainer;
typedef StackAllocatedComponentContainer<TransformComponent> TransformComponentContainer;
typedef StackAllocatedComponentContainer<UITransformComponent> UITransformComponentContainer;
