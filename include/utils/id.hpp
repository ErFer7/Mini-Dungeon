#pragma once

#include <memory>
#include <unordered_map>

#include "types.hpp"
#include "utils/uncopiable.hpp"

namespace utils {

typedef unsigned long long Id;

class IdReferences : public Uncopiable {
    friend class Identified;

   public:
    typedef std::unordered_map<Id, void *> IdReferenceMap;

    IdReferences() { this->_id_reference_map = std::make_unique<IdReferenceMap>(); }

    void *get_pointer(Id id) { return this->_id_reference_map->at(id); }

   private:
    void _set_pointer(Id id, void *pointer) { this->_id_reference_map->insert_or_assign(id, pointer); }

    // TODO: Implement _remove_pointer

   private:
    std::unique_ptr<std::unordered_map<Id, void *>> _id_reference_map;
};

class Identified : public Uncopiable {
   public:
    Identified(void *pointer);

    Identified(Identified &&other) noexcept = default;

    ~Identified();

    Identified &operator=(Identified &&other) noexcept = default;

    Id get_id() const { return _id; }

    void update_reference(void *pointer);

   private:
    static inline Id _next_id = 0ULL;
    Id _id;
};

}  // namespace utils
