#include "utils/activity_state.hpp"

#include "utils/id/identifiable.hpp"

using utils::ActivityState;
using utils::Handle;
using utils::Identified;

ActivityState::ActivityState(bool active, Handle<ActivityState> parent_activity_state)
    : _is_active(true),
      _is_self_active(true),
      _is_parent_active(true),
      Identified(this) {
    log_trace(this, __PRETTY_FUNCTION__);

    if (!parent_activity_state.is_null()) {
        this->_parent_update_listener.bind_callable<ActivityState, &ActivityState::_update_parent_activity>(
            this->make_handle<ActivityState>());
        this->_parent_update_listener.subscribe(parent_activity_state->get_activity_update_event());
    }
}

void ActivityState::set_parent_activity_state(Handle<ActivityState> parent_activity_state) {
    if (this->_parent_update_listener.is_subscribed()) {
        this->_parent_update_listener.unsubscribe_all();
    }

    if (!parent_activity_state.is_null()) {
        this->_parent_update_listener.bind_callable<ActivityState, &ActivityState::_update_parent_activity>(
            this->make_handle<ActivityState>());
        this->_parent_update_listener.subscribe(parent_activity_state->get_activity_update_event());

        this->_update_parent_activity(parent_activity_state->is_active());
    } else {
        this->_update_parent_activity(true);
    }
}

void ActivityState::_move(ActivityState &&other) {
    if (this == &other) {
        return;
    }

    this->update_reference(this);

    this->_is_active = std::move(other._is_active);
    this->_is_self_active = std::move(other._is_self_active);
    this->_is_parent_active = std::move(other._is_parent_active);
    this->_on_update_event = std::move(other._on_update_event);
    this->_parent_update_listener = std::move(other._parent_update_listener);
}
