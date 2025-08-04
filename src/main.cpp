#include "../include/game_core.hpp"

int main() {
    GameCore game_core = GameCore(1600, 800, "Mini Dungeon", 75, false, false, true);

    game_core.init_main_loop();

    return 0;
}
