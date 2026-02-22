#pragma once

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "components/text_component.hpp"
#include "components/ui_transform_component.hpp"
#include "containers/vector_container.hpp"
#include "types.hpp"

using utils::Handle;
using utils::Identified;

template <typename ComponentType>
class StackAllocatedComponentContainer : public VectorContainer<ComponentType> {
   public:
    StackAllocatedComponentContainer() : VectorContainer<ComponentType>() {}

    ~StackAllocatedComponentContainer() override = default;

    // The first type parameter is declared to satisfy the calls. See the HeapAllocatedComponentContainer
    template <typename, typename... Args>
    Handle<ComponentType> create_component(Handle<Entity> entity, Args &&...args) {
        ComponentType component = ComponentType(entity, std::forward<Args>(args)...);
        Handle<ComponentType> handle = static_cast<Identified *>(&component)->make_handle<ComponentType>();

        this->push_back(std::move(component));

        return handle;
    }

    template <typename>
    inline void destroy_component(ComponentType *component) {
        this->remove(component);
    }
};

class PhysicsComponentContainer final : public StackAllocatedComponentContainer<PhysicsComponent> {
    friend class PhysicsManager;
    friend class GraphicalDebuggingManager;
};

class ColliderComponentContainer final : public StackAllocatedComponentContainer<ColliderComponent> {
    friend class PhysicsManager;
    friend class GraphicalDebuggingManager;
};

class TransformComponentContainer final : public StackAllocatedComponentContainer<TransformComponent> {
    friend class GraphicalDebuggingManager;
};

typedef StackAllocatedComponentContainer<GraphicsComponent> GraphicsComponentContainer;
typedef StackAllocatedComponentContainer<TextComponent> TextComponentContainer;
typedef StackAllocatedComponentContainer<UITransformComponent> UITransformComponentContainer;
