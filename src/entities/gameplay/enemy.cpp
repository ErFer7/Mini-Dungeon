#include "entities/gameplay/enemy.hpp"

#include "components/behavior_components/enemy_component.hpp"
#include "components/behavior_components/player_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "entities/gameplay/player.hpp"

Enemy::Enemy(const EnemyArgs &args) : DynamicPhysicalEntity2D(args) {
    this->_walking_animation_component = this->create_component<WalkingAnimationComponent>();
    this->_enemy_component = this->create_component<EnemyComponent>(args);
}
