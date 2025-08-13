#pragma once

#include "../utils/game_core_dependency_injector.hpp"

using utils::GameCoreDependencyInjector;

class Container : public GameCoreDependencyInjector {
   public:
    Container() = default;

    Container(GameCore *game_core) : GameCoreDependencyInjector(game_core) {}

    virtual ~Container() = default;

    virtual void free() = 0;
};
