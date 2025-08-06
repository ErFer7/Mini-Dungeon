#pragma once

#include "../types.hpp"
#include "../utils/game_core_dependency_injector.hpp"

class Manager : public GameCoreDependencyInjector {
   public:
    Manager(GameCore *game_core) : GameCoreDependencyInjector(game_core){};

    virtual ~Manager() = default;

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};