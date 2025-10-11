#pragma once

#include "event.hpp"

using std::function;
using std::make_unique;
using std::move;
using std::remove;
using std::unique_ptr;
using std::vector;

namespace utils {

class ActivityState {
   public:
    typedef Event<bool> ActivityUpdateEvent;
    typedef ActivityUpdateEvent::Listener ActivityUpdateListener;

   public:
    ActivityState(bool active = true, ActivityState *parent_activity_state = nullptr)
        : _is_active(true), _is_self_active(true), _is_parent_active(true) {
        if (parent_activity_state != nullptr) {
            this->_parent_update_listener.set_callable([this](bool is_parent_active) { this->_update_parent_activity(is_parent_active); });
            this->_parent_update_listener.subscribe(parent_activity_state->get_activity_update_event());
        }
    }

    ~ActivityState() = default;

    inline void set_active(bool is_active) {
        this->_is_self_active = is_active;
        this->_update_activity();
    }

    inline bool is_active() { return this->_is_active; }

    inline ActivityUpdateEvent *get_activity_update_event() { return &this->_on_update_event; }

    void set_parent_activity_state(ActivityState *parent_activity_state) {
        if (this->_parent_update_listener.is_subscribed()) {
            this->_parent_update_listener.unsubscribe_all();
        }

        if (parent_activity_state != nullptr) {
            this->_parent_update_listener.set_callable([this](bool is_parent_active) { this->_update_parent_activity(is_parent_active); });
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
