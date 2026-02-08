#pragma once

#include "managers/manager.hpp"

class AudioComponentManager : public Manager {
    friend class AudioComponent;

   public:
    AudioComponentManager() = default;

    ~AudioComponentManager() override = default;

    void init() override {};
    void update() override {};
    void exit() override {};
};
