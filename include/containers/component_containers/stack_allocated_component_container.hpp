#pragma once

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "components/text_component.hpp"
#include "components/ui_transform_component.hpp"
#include "containers/vector_container.hpp"
#include "types.hpp"

template <typename ComponentType>
class StackAllocatedComponentContainer : public VectorContainer<ComponentType> {
   public:
    StackAllocatedComponentContainer() : VectorContainer<ComponentType>() {}

    ~StackAllocatedComponentContainer() override = default;

    // The first type parameter is declared to satisfy the calls. See the HeapAllocatedComponentContainer
    template <typename, typename... Args>
    utils::Handle<ComponentType> create_component(Entity *entity, Args &&...args) {
        ComponentType component = ComponentType(entity, std::forward<Args>(args)...);
        utils::Id component_id = static_cast<utils::Identified *>(&component)->get_id();
        utils::Handle<ComponentType> handle = utils::Handle<ComponentType>(component_id);

        this->push_back(std::move(component));

        return handle;
    }

    template <typename>
    inline void destroy_component(ComponentType *component) {
        this->remove(component);
    }
};

class PhysicsComponentContainer final : public StackAllocatedComponentContainer<PhysicsComponent> {
    friend class PhysicsComponentManager;
};

typedef StackAllocatedComponentContainer<ColliderComponent> ColliderComponentContainer;
typedef StackAllocatedComponentContainer<GraphicsComponent> GraphicsComponentContainer;
typedef StackAllocatedComponentContainer<TextComponent> TextComponentContainer;
typedef StackAllocatedComponentContainer<TransformComponent> TransformComponentContainer;
typedef StackAllocatedComponentContainer<UITransformComponent> UITransformComponentContainer;
