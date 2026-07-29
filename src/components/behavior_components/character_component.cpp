#include "components/behavior_components/character_component.hpp"

#include <raylib.h>

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/enemy_component.hpp"
#include "components/behavior_components/player_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "components/transform_component.hpp"
#include "entities/entity.hpp"
#include "entities/gameplay/player.hpp"

CharacterComponent::CharacterComponent(Handle<Entity> entity, const CharacterComponentArgs &args)
    : BehaviorComponent(entity) {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_max_health = args.max_health;
    this->_health = args.initial_health == -1 ? this->_max_health : args.initial_health;

    this->_transform_component = entity->get_component<TransformComponent>();
    this->_physics_component = entity->get_component<PhysicsComponent>();
    this->_walking_animation_component = entity->get_component<WalkingAnimationComponent>();
}

void CharacterComponent::_move(CharacterComponent &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->_health = std::move(other._health);
    this->_max_health = std::move(other._max_health);
    this->_transform_component = std::move(other._transform_component);
    this->_physics_component = std::move(other._physics_component);
    this->_walking_animation_component = std::move(other._walking_animation_component);
    this->_on_death_event = std::move(other._on_death_event);
}
