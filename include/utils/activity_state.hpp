#pragma once

#include "event.hpp"
#include "utils/id.hpp"

using std::make_unique;
using std::move;
using std::remove;
using std::unique_ptr;
using std::vector;

namespace utils {

class ActivityState : public Identified {
   public:
    typedef Event<bool> ActivityUpdateEvent;
    typedef ActivityUpdateEvent::Listener ActivityUpdateListener;

   public:
    ActivityState(bool active = true, Handle<ActivityState> parent_activity_state = Handle<ActivityState>())
        : _is_active(true),
          _is_self_active(true),
          _is_parent_active(true),
          utils::Identified(this) {
        log_trace(this, __FUNCTION__);

        if (!parent_activity_state.is_null()) {
            this->_parent_update_listener.bind_callable<ActivityState, &ActivityState::_update_parent_activity>(
                utils::Handle<ActivityState>(this->get_id()));
            this->_parent_update_listener.subscribe(parent_activity_state->get_activity_update_event());
        }
    }

    // TODO: Implement move semantics
    ActivityState(ActivityState &&other) = default;

    ~ActivityState() override { log_trace(this, __FUNCTION__); }

    ActivityState &operator=(ActivityState &&other) noexcept = default;

    inline void set_active(bool is_active) {
        this->_is_self_active = is_active;
        this->_update_activity();
    }

    inline bool is_active() { return this->_is_active; }

    inline utils::Handle<ActivityUpdateEvent> get_activity_update_event() {
        return utils::Handle<ActivityUpdateEvent>(this->_on_update_event.get_id());
    }

    void set_parent_activity_state(Handle<ActivityState> parent_activity_state) {
        if (this->_parent_update_listener.is_subscribed()) {
            this->_parent_update_listener.unsubscribe_all();
        }

        if (!parent_activity_state.is_null()) {
            this->_parent_update_listener.bind_callable<ActivityState, &ActivityState::_update_parent_activity>(
                utils::Handle<ActivityState>(this->get_id()));
            this->_parent_update_listener.subscribe(parent_activity_state->get_activity_update_event());

            this->_update_parent_activity(parent_activity_state->is_active());
        } else {
            this->_update_parent_activity(true);
        }
    }

   private:
    void _update_parent_activity(bool is_parent_active) {
        this->_is_parent_active = is_parent_active;
        this->_update_activity();
    }

    inline void _update_activity() {
        this->_is_active = this->_is_parent_active && this->_is_self_active;
        this->_on_update_event.invoke(this->_is_active);
    }

   private:
    bool _is_active;         // Resulting state
    bool _is_self_active;    // Intended state for this object
    bool _is_parent_active;  // State of its parent
    ActivityUpdateEvent _on_update_event;
    ActivityUpdateListener _parent_update_listener;
};

}  // namespace utils
