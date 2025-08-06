#pragma once

#include "../utils/game_core_dependency_injector.hpp"

class Scene : public GameCoreDependencyInjector {
   public:
    Scene() = default;

    Scene(GameCore *game_core) : GameCoreDependencyInjector(game_core){};

    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};
