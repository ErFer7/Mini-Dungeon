#include "components/collider_component.hpp"

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/physics_component.hpp"
#include "game_core.hpp"
#include "raylib.h"

ColliderComponent::ColliderComponent(GameCore *game_core, Entity *entity, const ColliderComponentArgs &args)
    : _rectangle(args.rectangle),
      Component(game_core, entity) {
    this->_transform_component = this->get_entity()->get_component<TransformComponent>();

    this->_transform_update_listener.set_callable(
        [this](const Vector2Df &, const TransformData &) { this->_update_rectangle(); });
    this->_transform_update_listener.subscribe(this->_transform_component->get_on_update_event());

    if (this->_rectangle.width == 0.0f && this->_rectangle.height == 0.0f) {
        GraphicsComponent *graphics_component = this->get_entity()->get_component<GraphicsComponent>();

        this->_rectangle = graphics_component->get_rectangle();
    }

    this->_update_rectangle();

    PhysicsComponent *physics_component = this->get_entity()->get_component<PhysicsComponent>();

    if (physics_component != nullptr) {
        physics_component->set_collider_component(this);
    }
}

// TODO: Add support for rotation
void ColliderComponent::_update_rectangle() {
    Vector2Df position = this->_transform_component->get_position();
    Vector2Df scale = this->_transform_component->get_scale();

    this->_rectangle.x = position.x;
    this->_rectangle.y = position.y;
    this->_rectangle.width = this->_rectangle.width * scale.x;
    this->_rectangle.height = this->_rectangle.height * scale.y;
}
