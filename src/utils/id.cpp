#include "utils/id.hpp"

#include "game_core.hpp"

utils::Identified::Identified(void *pointer) : _id(_next_id++) {
    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}

utils::Identified::~Identified() { GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, nullptr); }

void utils::Identified::update_reference(void *pointer) {
    GameCore::get_instance()->get_id_references()->_set_pointer(this->_id, pointer);
}
