#include "components/component.hpp"

#include "entities/entity.hpp"

Component::Component(Entity *entity) : _entity(entity), _activity_state(true, entity->get_activity_state()) {
    log_info("Component::Component(", entity, ')');
}
