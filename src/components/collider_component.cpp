#include "components/collider_component.hpp"

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "game_core.hpp"
#include "raylib.h"

ColliderComponent::ColliderComponent(GameCore *game_core, Entity *entity, const ColliderComponentArgs &args)
    : _rectangle(args.rectangle),
      Component(game_core, entity) {
    if (this->_rectangle.width == 0.0f && this->_rectangle.height == 0.0f) {
        GraphicsComponent *graphics_component = this->get_entity()->get_component<GraphicsComponent>();

        this->_rectangle = graphics_component->get_rectangle();
    }

    PhysicsComponent *physics_component = this->get_entity()->get_component<PhysicsComponent>();

    if (physics_component != nullptr) {
        physics_component->set_collider_component(this);
    }
}
