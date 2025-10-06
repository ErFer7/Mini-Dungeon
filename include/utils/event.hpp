#pragma once

#include <functional>
#include <memory>
#include <vector>

using std::function;
using std::make_unique;
using std::move;
using std::remove;
using std::unique_ptr;
using std::vector;

namespace utils {

template <typename... Args>
class Event {
    friend class Listener;

   public:
    class Listener {
        friend class Event;

       public:
        typedef vector<Event<Args...> *> EventVector;

        Listener() = default;

        Listener(function<void(Args...)> callable) : _callable(callable) { this->_events = make_unique<EventVector>(); }

        Listener(const Listener &other) { this->_copy(other); }

        Listener(Listener &&other) noexcept { this->_move(other); }

        ~Listener() { this->unsubscribe_all(); };

        inline Listener &operator=(const Listener &other) {
            this->_copy(other);

            return *this;
        }

        inline function<void(Args...)> get_callable() const { return this->_callable; }

        inline bool has_events() const { return !this->_events->empty(); }

        inline void subscribe(Event<Args...> *event) {
            this->_events->push_back(event);
            event->_add_listener(this);
        }

        inline void unsubscribe(Event<Args...> *event) {
            event->_remove_listener(this);
            this->_events->erase(remove(this->_events->begin(), this->_events->end(), event), this->_events->end());
        }

        void unsubscribe_all() {
            if (this->_events.get() == nullptr) {
                return;
            }

            for (auto &event : *this->_events) {
                event->_remove_listener(this);
            }

            this->_events->clear();
        }

       private:
        inline void _move(Listener &&other) {
            if (this != &other) {
                this->_callable = other._callable;
                this->_events.reset();
                this->_events = move(other._events);
            }
        }

        inline void _copy(const Listener &other) {
            if (this != &other) {
                this->_callable = other._callable;
                this->_events.reset();
                this->_events = make_unique<EventVector>(*other._events);
            }
        }

        inline void _call(Args... args) { this->_callable(args...); }

       private:
        function<void(Args...)> _callable;
        unique_ptr<EventVector> _events;
    };

    typedef vector<Listener *> ListenerVector;

   public:
    Event() { this->_listeners = make_unique<ListenerVector>(); }

    Event(const Event &other) { this->_copy(other); }

    Event(Event &&other) noexcept { this->_move(other); }

    ~Event() {
        for (const auto &listener : *this->_listeners) {
            listener->unsubscribe(this);
        }
    };

    inline Event &operator=(const Event &other) {
        this->_copy(other);

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
        _listeners->erase(remove(_listeners->begin(), _listeners->end(), listener), _listeners->end());
    }

    inline void _move(Event &&other) {
        if (this != &other) {
            this->_listeners.reset();
            this->_listeners = move(other._listeners);
        }
    }

    inline void _copy(const Event &other) {
        if (this != &other) {
            this->_listeners.reset();
            this->_listeners = make_unique<ListenerVector>(*other._listeners);
        }
    }

   private:
    unique_ptr<ListenerVector> _listeners;
};

}  // namespace utils
