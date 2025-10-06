#include "../../include/components/component.hpp"

#include "../../include/entities/entity.hpp"

Component::Component(GameCore *game_core, Entity *entity)
    : GameCoreDependencyInjector(game_core), _entity(entity), _activity_state(true, this->_entity->get_activity_state()) {}
