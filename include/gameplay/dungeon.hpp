#pragma once

#include "types.hpp"
#include "utils/game_core_dependency_injector.hpp"

using utils::GameCoreDependencyInjector;

class Dungeon : public GameCoreDependencyInjector {
   public:
    Dungeon() = default;

    Dungeon(GameCore *game_core) : GameCoreDependencyInjector(game_core){};

    ~Dungeon() = default;
};