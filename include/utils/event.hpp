#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "utils/debug.hpp"
#include "utils/id/handle.hpp"
#include "utils/id/identifiable.hpp"

namespace utils {

template <typename... Args>
class Event final : public Identified {
    friend class Listener;

   public:
    class Listener final : public Identified {
        friend class Event;

       public:
        typedef std::vector<Handle<Event<Args...>>> EventVector;

        Listener() : Identified(this) {
            log_trace(this, __PRETTY_FUNCTION__);

            this->_events = std::make_unique<EventVector>();
        };

        Listener(Listener &&other) noexcept : Identified(std::move(other)) { this->_move(std::move(other)); }

        ~Listener() {
            log_trace(this, __PRETTY_FUNCTION__);

            if (this->_events == nullptr) {
                return;
            }

            this->unsubscribe_all();
        };

        inline Listener &operator=(Listener &&other) noexcept {
            Identified::operator=(std::move(other));

            this->_move(std::move(other));

            return *this;
        }

        template <typename Type, auto Method>
        inline void bind_callable(Handle<Type> handle) {
            this->_handle = handle;

            this->_invoker = [](const Handle<void> &generic_handle, Args... args) {
                void *pointer = generic_handle.get_pointer();
                Type *instance = static_cast<Type *>(pointer);

                if (instance != nullptr) {
                    (instance->*Method)(args...);
                }
            };
        }

        inline bool is_subscribed() const { return !this->_events->empty(); }

        inline void subscribe(Handle<Event<Args...>> event) {
            this->_events->push_back(event);
            event->_add_listener(this->make_handle<Listener>());
        }

        inline void unsubscribe(Handle<Event<Args...>> event) {
            event->_remove_listener(this->make_handle<Listener>());
            this->_events->erase(std::remove(this->_events->begin(), this->_events->end(), event),
                                 this->_events->end());
        }

        void unsubscribe_all() {
            log_trace(this, __PRETTY_FUNCTION__);

            for (auto &event : *this->_events) {
                if (!event.is_null()) {
                    event->_remove_listener(this->make_handle<Listener>());
                }
            }

            this->_events->clear();
        }

       private:
        inline void _move(Listener &&other) {
            log_trace(this, __PRETTY_FUNCTION__, &other);

            if (this == &other) {
                return;
            }

            this->update_reference(this);

            this->_handle = std::move(other._handle);
            this->_invoker = std::move(other._invoker);
            this->_events = std::move(other._events);
        }

        inline void _call(Args... args) {
            if (this->_invoker != nullptr) {
                this->_invoker(_handle, args...);
            }
        }

       private:
        Handle<void> _handle;
        void (*_invoker)(const Handle<void> &, Args...);
        std::unique_ptr<EventVector> _events;
    };

    typedef std::vector<Handle<Listener>> ListenerVector;

   public:
    Event() : Identified(this) {
        log_trace(this, __PRETTY_FUNCTION__);

        this->_listeners = std::make_unique<ListenerVector>();
    }

    // Events can't be copied because of listeners (see above)
    Event(const Event &other) noexcept = delete;

    Event(Event &&other) noexcept : Identified(std::move(other)) { this->_move(std::move(other)); }

    ~Event() {
        log_trace(this, __PRETTY_FUNCTION__);

        if (this->_listeners == nullptr) {
            return;
        }

        for (const auto &listener : *this->_listeners) {
            if (!listener.is_null()) {
                listener->unsubscribe(this->make_handle<Event>());
            }
        }
    };

    inline Event &operator=(const Event &other) noexcept = delete;

    inline Event &operator=(Event &&other) noexcept {
        Identified::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline void invoke(Args... args) {
        log_trace(this, __PRETTY_FUNCTION__, std::forward<Args>(args)...);

        for (const auto &listener : *this->_listeners) {
            log_info(this, "Event: Calling on listener ", listener);
            listener->_call(args...);
        }
    }

    inline bool has_listeners() { return !this->_listeners->empty(); }

   private:
    inline void _add_listener(Handle<Listener> listener) {
        log_trace(this, __PRETTY_FUNCTION__, listener);
        this->_listeners->push_back(listener);
    }

    inline void _remove_listener(Handle<Listener> listener) {
        log_trace(this, __PRETTY_FUNCTION__, listener);
        _listeners->erase(std::remove(_listeners->begin(), _listeners->end(), listener), _listeners->end());
    }

    inline void _move(Event &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->update_reference(this);

        this->_listeners = std::move(other._listeners);
    }

   private:
    std::unique_ptr<ListenerVector> _listeners;
};

}  // namespace utils
