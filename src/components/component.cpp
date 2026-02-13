#include "components/component.hpp"

#include "entities/entity.hpp"
#include "utils/id.hpp"

Component::Component(Entity *entity)
    : _entity(entity),
      _activity_state(true, entity->get_activity_state()),
      utils::Identified(static_cast<void *>(this)) {
    utils::log_trace(this, __FUNCTION__, entity);
}
