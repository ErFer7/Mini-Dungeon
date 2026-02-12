#include "utils/id.hpp"

#include "game_core.hpp"
#include "utils/debug.hpp"

utils::Identified::Identified(void *pointer) : _id(_next_id++) {
    utils::log_trace(__FUNCTION__, pointer);
    utils::log_info("Identified ID: ", this->_id);

    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}

utils::Identified &utils::Identified::operator=(Identified &&other) noexcept {
    if (this != &other) {
        this->_id = other._id;
        this->update_reference(this);
        other._id = -1;
    }

    return *this;
}

utils::Identified::~Identified() {
    if (this->_id != -1) {
        GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, nullptr);
    }
}

void utils::Identified::update_reference(void *pointer) {
    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}

void *utils::HandlHelper::_get_pointer(utils::Id id) {
    return GameCore::get_instance()->get_id_references()->get_pointer(id);
}
