#pragma once

#include <memory>
#include <utility>

using std::forward;
using std::make_unique;
using std::unique_ptr;

class GameCore;

namespace utils {

class GameCoreDependencyInjector {
   public:
    GameCoreDependencyInjector() = default;

    GameCoreDependencyInjector(GameCore *game_core) : _game_core(game_core){};

    virtual ~GameCoreDependencyInjector() = default;

    inline GameCore *get_game_core() const { return this->_game_core; }

    template <typename T, typename... Args>
    T create(Args &&...args) {
        return T(this->_game_core, forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    T *create_heap_allocated(Args &&...args) {
        return new T(this->_game_core, forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    unique_ptr<T> create_unique(Args &&...args) {
        return make_unique<T>(this->_game_core, forward<Args>(args)...);
    }

   private:
    GameCore *_game_core;
};

}  // namespace utils
