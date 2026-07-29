#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/character_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;

struct PlayerComponentArgs {
    Handle<Sword> sword;
    int max_health;
    int initial_health = -1;

    operator CharacterComponentArgs() const { return CharacterComponentArgs{max_health, initial_health}; }
};

class PlayerComponent : public CharacterComponent {
   public:
    PlayerComponent(Handle<Entity> entity, const PlayerComponentArgs &args = PlayerComponentArgs());

    PlayerComponent(PlayerComponent &&other) noexcept : CharacterComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~PlayerComponent() override {}

    inline PlayerComponent &operator=(PlayerComponent &&other) noexcept {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    void update() override;

   private:
    inline void _move(PlayerComponent &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->_sword = std::move(other._sword);
    }

   private:
    Handle<Sword> _sword;
};
