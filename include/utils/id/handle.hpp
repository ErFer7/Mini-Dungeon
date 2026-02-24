#pragma once

#include "types.hpp"
#include "utils/id/id_references.hpp"

namespace utils {

class HandleHelper {
    template <typename Type>
    friend class Handle;

   private:
    static void *_get_pointer(Id id);
};

template <typename Type>
class Handle {
    template <typename DerivedType>
    friend class Handle;  // Friends are the handles we cast along the way

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

    inline bool is_null() const { return this->_id < 0 || HandleHelper::_get_pointer(this->_id) == nullptr; }

    inline Type *get_pointer() const { return static_cast<Type *>(HandleHelper::_get_pointer(this->_id)); }

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

    // TODO: This could mislead the comparison between what is null (ID !-> 0) or what is valid (Id != -1)
    inline bool is_null() const { return this->_id < 0 || HandleHelper::_get_pointer(this->_id) == nullptr; }

    inline void *get_pointer() const { return HandleHelper::_get_pointer(this->_id); }

    inline Id get_id() const { return _id; }

   private:
    Id _id;
};

inline std::ostream &operator<<(std::ostream &ostream, const Handle<void> &handle) {
    ostream << "Handle { id: " << handle.get_id() << "}";

    return ostream;
}

}  // namespace utils
