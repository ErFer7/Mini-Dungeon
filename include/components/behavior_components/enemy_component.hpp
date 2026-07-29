#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/character_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;

struct EnemyComponentArgs {
    Handle<Player> player;
    int max_health;
    int initial_health = -1;

    operator CharacterComponentArgs() const { return CharacterComponentArgs{max_health, initial_health}; }
};

class EnemyComponent : public CharacterComponent {
   public:
    EnemyComponent(Handle<Entity> entity, const EnemyComponentArgs &args = EnemyComponentArgs());

    EnemyComponent(EnemyComponent &&other) noexcept : CharacterComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~EnemyComponent() override {}

    inline EnemyComponent &operator=(EnemyComponent &&other) noexcept {
        EnemyComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    void update() override;

   private:
    void _move(EnemyComponent &&other);

   private:
    Handle<Player> _player;
};
