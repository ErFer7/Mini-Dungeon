#pragma once

#include <memory>
#include <unordered_map>

#include "types.hpp"
#include "utils/debug.hpp"
#include "utils/uncopiable.hpp"

namespace utils {

typedef long long Id;

// TODO: Implement _remove_pointer
class IdReferences : public Uncopiable {
    friend class Identified;

   public:
    typedef std::unordered_map<Id, void *> IdReferenceMap;

   public:
    // TODO: Check if inplace creation can lead to memory leaks here
    IdReferences() { this->_id_reference_map = std::make_unique<IdReferenceMap>(); }

    ~IdReferences() = default;

    inline void *get_pointer(Id id) { return this->_id_reference_map->at(id); }

   private:
    inline void _set_pointer(Id id, void *pointer) {
        log_trace(this, __PRETTY_FUNCTION__, id, pointer);

        this->_id_reference_map->insert_or_assign(id, pointer);
    }

   private:
    std::unique_ptr<IdReferenceMap> _id_reference_map;
};

}  // namespace utils
