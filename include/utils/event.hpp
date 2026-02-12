#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "utils/id.hpp"
#include "utils/uncopiable.hpp"

namespace utils {

// TODO: Rewrite this entire class considering that addresses could change, move semantics, etc.
// It should be capable of handling everything
template <typename... Args>
class Event : public Uncopiable {
    friend class Listener;

   public:
    class Listener : public Uncopiable {
        friend class Event;

       public:
        typedef std::vector<Event<Args...> *> EventVector;

        Listener() { this->_events = std::make_unique<EventVector>(); };

        Listener(Listener &&other) noexcept { this->_move(std::move(other)); }

        ~Listener() {
            if (this->_events == nullptr) {
                return;
            }

            this->unsubscribe_all();
        };

        inline Listener &operator=(Listener &&other) {
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

        inline void subscribe(Event<Args...> *event) {
            this->_events->push_back(event);
            event->_add_listener(this);
        }

        inline void unsubscribe(Event<Args...> *event) {
            event->_remove_listener(this);
            this->_events->erase(std::remove(this->_events->begin(), this->_events->end(), event),
                                 this->_events->end());
        }

        void unsubscribe_all() {
            for (auto &event : *this->_events) {
                event->_remove_listener(this);
            }

            this->_events->clear();
        }

       private:
        inline void _move(Listener &&other) {
            if (this != &other) {
                // other->unsubscribe_all();

                this->_handle = std::move(other._handle);
                this->_invoker = std::move(other._invoker);
                this->_events = std::move(other._events);

                // for (auto &event : *this->_events) {
                //     event->_add_listener(this);
                // }
            }
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

    typedef std::vector<Listener *> ListenerVector;

   public:
    Event() { this->_listeners = std::make_unique<ListenerVector>(); }

    // Events can't be copied because of listeners (see above)
    Event(const Event &other) noexcept = delete;

    Event(Event &&other) noexcept { this->_move(std::move(other)); }

    ~Event() {
        if (this->_listeners == nullptr) {
            return;
        }

        for (const auto &listener : *this->_listeners) {
            listener->unsubscribe(this);
        }
    };

    inline Event &operator=(const Event &other) noexcept = delete;

    inline Event &operator=(Event &&other) {
        this->_move(std::move(other));

        return *this;
    }

    inline void invoke(Args... args) {
        for (const auto &listener : *this->_listeners) {
            listener->_call(args...);
        }
    }

    inline bool has_listeners() { return !this->_listeners->empty(); }

   private:
    inline void _add_listener(Listener *listener) { this->_listeners->push_back(listener); }

    inline void _remove_listener(Listener *listener) {
        _listeners->erase(std::remove(_listeners->begin(), _listeners->end(), listener), _listeners->end());
    }

    // FIX: This is breaking
    inline void _move(Event &&other) {
        if (this != &other) {
            this->_listeners.reset();
            this->_listeners = std::move(other._listeners);
        }
    }

   private:
    std::unique_ptr<ListenerVector> _listeners;
};

}  // namespace utils
