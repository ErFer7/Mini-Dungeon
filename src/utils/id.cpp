#include "utils/id.hpp"

#include "game_core.hpp"
#include "utils/debug.hpp"

utils::Identified::Identified(void *pointer) : _id(_next_id++) {
    utils::log_trace(this, __PRETTY_FUNCTION__, pointer);
    utils::log_info("Identified ID: ", this->_id);

    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}

utils::Identified::~Identified() {
    utils::log_trace(this, __PRETTY_FUNCTION__);

    if (this->_id != -1LL) {
        GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, nullptr);
    }
}

void utils::Identified::update_reference(void *pointer) {
    utils::log_trace(this, __PRETTY_FUNCTION__, pointer);

    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}

void *utils::HandlHelper::_get_pointer(utils::Id id) {
    return GameCore::get_instance()->get_id_references()->get_pointer(id);
}
