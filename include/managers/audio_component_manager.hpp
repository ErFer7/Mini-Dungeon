#pragma once

#include "managers/component_manager.hpp"

class AudioComponentManager : public ComponentManager {
    friend class AudioComponent;

   public:
    AudioComponentManager() = default;

    AudioComponentManager(GameCore *game_core) : ComponentManager(game_core){};

    ~AudioComponentManager() override = default;

    void init() override {};
    void update() override {};
    void exit() override {};
};
