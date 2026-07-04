#include "components/behavior_components/player_component.hpp"

#include <raylib.h>

#include <cmath>

#include "components/behavior_components/behavior_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "definitions.hpp"
#include "entities/entity.hpp"

PlayerComponent::PlayerComponent(Handle<Entity> entity) : BehaviorComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_transform_component = entity->get_component<TransformComponent>();
    this->_physics_component = entity->get_component<PhysicsComponent>();
}

void PlayerComponent::update() {
    GameCore::get_graphics_manager()->set_camera_position(this->_transform_component->get_position());

    if (IsKeyDown(KEY_UP)) {
        this->_physics_component->set_velocity_y(PLAYER_SPEED);
    } else if (IsKeyDown(KEY_DOWN)) {
        this->_physics_component->set_velocity_y(-PLAYER_SPEED);
    }

    // TODO: Implement the animation system
    if (IsKeyDown(KEY_RIGHT)) {
        this->_physics_component->set_velocity_x(PLAYER_SPEED);
        if (this->get_entity()->get_component<GraphicsComponent>()->is_flipped_horizontally()) {
            this->get_entity()->get_component<GraphicsComponent>()->flip_horizontally();
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        this->_physics_component->set_velocity_x(-PLAYER_SPEED);

        if (!this->get_entity()->get_component<GraphicsComponent>()->is_flipped_horizontally()) {
            this->get_entity()->get_component<GraphicsComponent>()->flip_horizontally();
        }
    }

    if (!this->_physics_component->get_velocity().is_approximately_zero()) {
        this->get_entity()->get_component<GraphicsComponent>()->set_offset(Vector2Df(
            0.0f, std::sin(GetTime() * 50.0f) * this->_physics_component->get_velocity().magnitude() * 0.025f));
    }
}

void PlayerComponent::_move(PlayerComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_physics_component = std::move(other._physics_component);
}
