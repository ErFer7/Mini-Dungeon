#include "utils/id.hpp"

#include "game_core.hpp"
#include "utils/debug.hpp"

using utils::HandleHelper;
using utils::Identified;

Identified::Identified(void *pointer) : _id(_next_id++) {
    log_trace(this, __PRETTY_FUNCTION__, pointer);
    log_info(this, "Identified: ID = ", this->_id);

    GameCore::get_id_references()->_set_pointer(this->_id, pointer);
}

Identified::~Identified() {
    log_trace(this, __PRETTY_FUNCTION__);

    if (this->_id != -1LL) {
        GameCore::get_id_references()->_set_pointer(this->_id, nullptr);
    }
}

void Identified::update_reference(void *pointer) {
    log_trace(this, __PRETTY_FUNCTION__, pointer);

    GameCore::get_id_references()->_set_pointer(this->_id, pointer);
}

void *HandleHelper::_get_pointer(utils::Id id) { return GameCore::get_id_references()->get_pointer(id); }
