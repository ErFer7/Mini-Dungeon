#pragma once

#include <iostream>

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
        : _is_active(true), _is_self_active(true), _is_parent_active(true), _parent_activity_state(parent_activity_state) {
        // TODO: Fix this
        if (this->_parent_activity_state != nullptr) {
            this->_parent_update_listener =
                ActivityUpdateListener([this](bool is_parent_active) { this->_update_parent_activity(is_parent_active); });
            this->_parent_update_listener.subscribe(this->_parent_activity_state->get_activity_update_event());
        }
    }

    ~ActivityState() = default;

    inline void set_active(bool is_active) {
        this->_is_self_active = is_active;
        this->_update_activity();
        std::cout << "set: " << this->_on_update_event.has_listeners() << std::endl;
        this->_on_update_event.invoke(this->_is_active);
    }

    inline bool is_active() { return this->_is_active; }

    inline ActivityUpdateEvent *get_activity_update_event() { return &this->_on_update_event; }

   private:
    void _update_parent_activity(bool is_parent_active) {
        this->_is_parent_active = is_parent_active;
        std::cout << "debug: " << is_parent_active << std::endl;
        this->_update_activity();
    }

    void _update_activity() { this->_is_active = this->_is_parent_active && this->_is_self_active; }

   private:
    bool _is_active;         // Resulting state
    bool _is_self_active;    // Intended state for this object
    bool _is_parent_active;  // State of its parent
    ActivityState *_parent_activity_state;
    ActivityUpdateEvent _on_update_event;
    ActivityUpdateListener _parent_update_listener;
};

}  // namespace utils
