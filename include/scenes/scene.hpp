#pragma once

#include "types.hpp"
#include "utils/game_core_dependency_injector.hpp"

using utils::GameCoreDependencyInjector;

class Scene : public GameCoreDependencyInjector {
   public:
    Scene() = default;

    Scene(GameCore *game_core) : _was_initialized(false), GameCoreDependencyInjector(game_core){};

    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void enter() = 0;

    virtual void update() = 0;

    virtual void leave() = 0;

    virtual void exit() = 0;

    inline bool was_initialized() { return this->_was_initialized; }

   protected:
    bool _was_initialized;
};
