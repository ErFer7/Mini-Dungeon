#pragma once

#include "../types.hpp"
#include "../utils/engine_core_dependency_injector.hpp"

class Manager : public EngineCoreDependencyInjector {
   public:
    Manager(EngineCore *engine_core) : EngineCoreDependencyInjector(engine_core){};

    virtual ~Manager() = default;

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};