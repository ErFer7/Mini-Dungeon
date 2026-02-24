#include "utils/id/handle.hpp"

#include "game_core.hpp"
#include "utils/debug.hpp"
#include "utils/id/id_references.hpp"

using utils::HandleHelper;
using utils::Id;

void *HandleHelper::_get_pointer(Id id) { return GameCore::get_id_references()->get_pointer(id); }
