#pragma once

#include "../utils/game_core_dependency_injector.hpp"

class AssetContainer : public GameCoreDependencyInjector {
   public:
    AssetContainer() = default;

    AssetContainer(GameCore *game_core);

    ~AssetContainer();
};
