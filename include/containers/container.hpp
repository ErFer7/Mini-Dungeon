#pragma once

#include "utils/game_core_dependency_injector.hpp"

using utils::GameCoreDependencyInjector;

template <typename DataStructure, typename Identifier, typename Object>
class Container : public GameCoreDependencyInjector {
   public:
    Container() = default;

    Container(GameCore *game_core) : GameCoreDependencyInjector(game_core) {}

    virtual ~Container() = default;

    virtual void insert(Identifier identifier, const Object object) = 0;

    virtual Object &get(Identifier identifier) const = 0;

    virtual Object *get_ref(Identifier identifier) const = 0;

    virtual void remove(Identifier identifier) = 0;

    virtual void remove(const Object &object) = 0;

    virtual void free() = 0;

    virtual size_t size() const = 0;

   protected:
    virtual DataStructure *get_data_structure() = 0;
};
