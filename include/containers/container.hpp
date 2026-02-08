#pragma once

#include <cstddef>

template <typename DataStructure, typename Identifier, typename Object>
class Container {
   public:
    Container() = default;

    virtual ~Container() = default;

    virtual void insert(Identifier identifier, Object &&object) = 0;

    virtual Object &get(Identifier identifier) const = 0;

    virtual Object *get_ref(Identifier identifier) const = 0;

    virtual void remove(Identifier identifier) = 0;

    virtual void remove(const Object &object) = 0;

    virtual void free() = 0;

    virtual size_t size() const = 0;

   protected:
    virtual DataStructure *get_data_structure() = 0;
};
