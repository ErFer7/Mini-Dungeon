#pragma once

#include "event.hpp"
#include "utils/id/identifiable.hpp"

namespace utils {

class ActivityState : public Identified {
   public:
    typedef Event<bool> ActivityUpdateEvent;
    typedef ActivityUpdateEvent::Listener ActivityUpdateListener;

   public:
    ActivityState(bool active = true, Handle<ActivityState> parent_activity_state = Handle<ActivityState>());

    ActivityState(ActivityState &&other) noexcept : Identified(std::move(other)) { this->_move(std::move(other)); }

    ~ActivityState() override { log_trace(this, __PRETTY_FUNCTION__); }

    ActivityState &operator=(ActivityState &&other) noexcept {
        Identified::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline void set_active(bool is_active) {
        this->_is_self_active = is_active;
        this->_update_activity();
    }

    inline bool is_active() const { return this->_is_active; }

    inline Handle<ActivityUpdateEvent> get_activity_update_event() {
        return this->_on_update_event.make_handle<ActivityUpdateEvent>();
    }

    void set_parent_activity_state(Handle<ActivityState> parent_activity_state);

   private:
    void _move(ActivityState &&other);

    inline void _update_parent_activity(bool is_parent_active) {
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
