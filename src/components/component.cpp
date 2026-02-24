#include "components/component.hpp"

#include "entities/entity.hpp"

using utils::log_trace;

Component::Component(Handle<Entity> entity)
    : _entity(entity),
      _activity_state(true, entity->get_activity_state()),
      Identified(this) {
    log_trace(this, __PRETTY_FUNCTION__, entity);
}

void Component::_move(Component &&other) {
    log_trace(this, __PRETTY_FUNCTION__, &other);

    if (this == &other) {
        return;
    }

    this->update_reference(this);

    this->_entity = std::move(other._entity);
    this->_on_destroy_event = std::move(other._on_destroy_event);
    this->_activity_state = std::move(other._activity_state);
}
