#pragma once

#include "types.hpp"
#include "utils/id.hpp"

class Scene : public utils::Identified {
   public:
    Scene() : _was_initialized(false), utils::Identified(this) {};

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
