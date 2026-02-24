#pragma once

#include "components/component.hpp"
#include "managers/behavior_manager.hpp"
#include "utils/debug.hpp"

using utils::Handle;
using utils::log_trace;

class BehaviorComponent : public Component {
    friend class BehaviorManager;

   public:
    BehaviorComponent(Handle<Entity> entity) : Component(entity) { log_trace(this, __PRETTY_FUNCTION__, entity); }

    BehaviorComponent(BehaviorComponent &&other) noexcept : Component(std::move(other)) {
        this->_move(std::move(other));
    }

    ~BehaviorComponent() override { log_trace(this, __PRETTY_FUNCTION__); }

    inline BehaviorComponent &operator=(BehaviorComponent &&other) noexcept {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    virtual void start() {}

    virtual void update() {}

    virtual void debug_draw() override {}

   private:
    inline void _move(BehaviorComponent &&other) { log_trace(this, __PRETTY_FUNCTION__, &other); }
};
