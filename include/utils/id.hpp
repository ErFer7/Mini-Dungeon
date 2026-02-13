#pragma once

#include <memory>
#include <unordered_map>

#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/uncopiable.hpp"

namespace utils {

typedef long long Id;

class IdReferences : public Uncopiable {
    friend class Identified;

   public:
    typedef std::unordered_map<Id, void *> IdReferenceMap;

    IdReferences() { this->_id_reference_map = std::make_unique<IdReferenceMap>(); }

    void *get_pointer(Id id) { return this->_id_reference_map->at(id); }

   private:
    void _set_pointer(Id id, void *pointer) {
        log_trace(this, __FUNCTION__, id, pointer);

        this->_id_reference_map->insert_or_assign(id, pointer);
    }

    // TODO: Implement _remove_pointer

   private:
    std::unique_ptr<std::unordered_map<Id, void *>> _id_reference_map;
};

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

    Id get_id() const { return _id; }

    void update_reference(void *pointer);

   private:
    void _move(Identified &&other) {
        log_trace(this, __FUNCTION__, &other);

        if (this != &other) {
            this->_id = other._id;
            other._id = -1LL;
        }
    }

   private:
    static inline Id _next_id = 0LL;
    Id _id;
};

class HandlHelper {
    template <typename Type>
    friend class Handle;

   private:
    static void *_get_pointer(Id id);
};

template <typename Type>
class Handle {
    template <typename DerivedType>
    friend class Handle;  // Friends are the handles we casted along the way

   public:
    Handle() : _id(-1LL) {}

    Handle(Id id) : _id(id) {}

    // Allows upcasting
    template <typename OtherType, std::enable_if_t<std::is_convertible_v<OtherType *, Type *>, int> = 0>
    Handle(const Handle<OtherType> &other) : _id(other._id) {}

    // Allows downcasting
    template <typename OtherType,
              std::enable_if_t<!std::is_convertible_v<OtherType *, Type *> && std::is_base_of_v<OtherType, Type>,
                               bool> = true>
    explicit Handle(const Handle<OtherType> &other) : _id(other._id) {}

    inline Type *operator->() const noexcept { return this->get_pointer(); }

    inline Type &operator*() const { return *this->get_pointer(); }

    inline bool operator==(Handle<Type> &other) const { return this->_id == other._id; }

    inline bool is_null() const { return this->_id < 0 || HandlHelper::_get_pointer(this->_id) == nullptr; }

    inline Type *get_pointer() const { return static_cast<Type *>(HandlHelper::_get_pointer(this->_id)); }

   private:
    Id _id;
};

template <>
class Handle<void> {
    template <typename DerivedType>
    friend class Handle;

   public:
    Handle() : _id(-1LL) {}

    Handle(Id id) : _id(id) {}

    template <typename OtherType>
    Handle(const Handle<OtherType> &other) : _id(other._id) {}

    inline bool is_null() const { return this->_id < 0 || HandlHelper::_get_pointer(this->_id) == nullptr; }

    inline void *get_pointer() const { return HandlHelper::_get_pointer(this->_id); }

    inline Id get_id() const { return _id; }

   private:
    Id _id;
};

inline std::ostream &operator<<(std::ostream &ostream, const Handle<void> &handle) {
    ostream << "Handle {" << handle.get_id() << "}";

    return ostream;
}

}  // namespace utils
