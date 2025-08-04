#pragma once

#include <memory>
#include <utility>

class EngineCore;

class EngineCoreDependencyInjector {
   public:
    EngineCoreDependencyInjector() = default;

    EngineCoreDependencyInjector(EngineCore *engine_core) : _engine_core(engine_core){};

    virtual ~EngineCoreDependencyInjector() = default;

    inline EngineCore *get_engine_core() const { return this->_engine_core; }

    template <typename T, typename... Args>
    T create(Args &&...args) {
        return T(this->_engine_core, std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    T *create_heap_allocated(Args &&...args) {
        return new T(this->_engine_core, std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    std::unique_ptr<T> create_unique(Args &&...args) {
        return std::make_unique<T>(this->_engine_core, std::forward<Args>(args)...);
    }

   private:
    EngineCore *_engine_core;
};