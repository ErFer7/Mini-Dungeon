#pragma once

#include "types.hpp"

class Scene {
   public:
    Scene() : _was_initialized(false) {};

    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void enter() = 0;

    virtual void update() = 0;

    virtual void leave() = 0;

    virtual void exit() = 0;

    inline bool was_initialized() { return this->_was_initialized; }

   protected:
    bool _was_initialized;
};
