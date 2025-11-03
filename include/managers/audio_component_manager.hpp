#pragma once

#include "managers/manager.hpp"

class AudioComponentManager : public Manager {
    friend class AudioComponent;

   public:
    AudioComponentManager() = default;

    AudioComponentManager(GameCore *game_core) : Manager(game_core){};

    ~AudioComponentManager() override = default;

    void init() override {};
    void update() override {};
    void exit() override {};
};
