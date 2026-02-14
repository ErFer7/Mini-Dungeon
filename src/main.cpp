#include "game_core.hpp"

int main() {
    GameCore::init_game_core(1200, 720, "Mini Dungeon", 75, true, false, true);
    GameCore::get_instance()->init_main_loop();

    return 0;
}
