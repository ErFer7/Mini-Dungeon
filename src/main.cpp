#include "game_core.hpp"

int main() {
    GameCore game_core = GameCore(1200, 720, "Mini Dungeon", 75, false, false, true);

    game_core.init_main_loop();

    return 0;
}
