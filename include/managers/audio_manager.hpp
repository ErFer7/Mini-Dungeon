#pragma once

#include "managers/manager.hpp"

class AudioManager : public Manager {
    friend class AudioComponent;

   public:
    AudioManager() = default;

    ~AudioManager() override = default;

    void init() override {};
    void update() override {};
    void exit() override {};
};
