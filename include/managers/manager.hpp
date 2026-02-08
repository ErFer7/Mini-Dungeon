#pragma once

#include "types.hpp"

class Manager {
   public:
    Manager() = default;

    virtual ~Manager() = default;

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};
