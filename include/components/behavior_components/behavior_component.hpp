#pragma once

#include "components/component.hpp"
#include "managers/behavior_component_manager.hpp"
#include "utils/debug.hpp"

using utils::Handle;
using utils::log_trace;

class BehaviorComponent : public Component {
    friend class BehaviorComponentManager;

   public:
    BehaviorComponent(Handle<Entity> entity) : Component(entity) { log_trace(this, __PRETTY_FUNCTION__, entity); }

    BehaviorComponent(BehaviorComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~BehaviorComponent() override { log_trace(this, __PRETTY_FUNCTION__); };

    BehaviorComponent &operator=(BehaviorComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    virtual void start() {};

    virtual void update() {};

   private:
    void _move(BehaviorComponent &&other) { log_trace(this, __PRETTY_FUNCTION__, &other); }
};
