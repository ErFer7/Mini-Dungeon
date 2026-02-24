#pragma once

#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/id/id_references.hpp"
#include "utils/uncopiable.hpp"

namespace utils {

// TODO: Find a way to make this more reliable.
// We are currently relying on the way things are oriented in memory to cast between types.
// Multiple inheritance could break everything.
class Identified : public Uncopiable {
   public:
    Identified(void *pointer);

    Identified(Identified &&other) noexcept { this->_move(std::move(other)); }

    ~Identified();

    Identified &operator=(Identified &&other) noexcept {
        this->_move(std::move(other));

        return *this;
    }

    inline Id get_id() const { return _id; }

    void update_reference(void *pointer);

    template <typename Type>
    inline Handle<Type> make_handle() {
        return Handle<Type>(this->_id);
    }

   private:
    void _move(Identified &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->_id = std::move(other._id);
        other._id = -1LL;
    }

   private:
    static inline Id _next_id = 0LL;
    Id _id;
};

}  // namespace utils
