#pragma once

#include <concepts>
#include <cstddef>

#include "utils/id.hpp"

template <typename DataStructure, typename LocalIdentifier, typename Object>
    requires std::derived_from<Object, utils::Identified>
class Container {
   public:
    Container() = default;

    virtual ~Container() = default;

    virtual void insert(LocalIdentifier local_identifier, Object &&object) = 0;

    virtual Object &get(LocalIdentifier local_identifier) const = 0;

    virtual Object *get_ref(LocalIdentifier local_identifier) const = 0;

    virtual void remove(LocalIdentifier local_identifier) = 0;

    virtual void remove(const Object &object) = 0;

    virtual void free() = 0;

    virtual size_t size() const = 0;

   protected:
    virtual DataStructure *get_data_structure() = 0;
};
