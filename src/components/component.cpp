#include "components/component.hpp"

#include "entities/entity.hpp"
#include "utils/id.hpp"

Component::Component(Handle<Entity> entity)
    : _entity(entity),
      _activity_state(true, entity->get_activity_state()),
      Identified(this) {
    log_trace(this, __PRETTY_FUNCTION__, entity);
}
