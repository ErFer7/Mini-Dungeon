#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/behavior_components/walking_animation_component.hpp"
#include "components/physics_component.hpp"
#include "types.hpp"

using utils::Handle;

struct CharacterComponentArgs {
    int max_health;
    int initial_health = -1;  // -1 is the blank value
};

class CharacterComponent : public BehaviorComponent {
   public:
    typedef Event<Handle<Entity>> DeathEvent;
    typedef DeathEvent::Listener DeathListener;

   public:
    CharacterComponent(Handle<Entity> entity, const CharacterComponentArgs &args = CharacterComponentArgs());

    CharacterComponent(CharacterComponent &&other) noexcept : BehaviorComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~CharacterComponent() override {}

    inline CharacterComponent &operator=(CharacterComponent &&other) noexcept {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    virtual void update() override {}

    inline void apply_health_change(int change) {
        this->_health += change;

        if (this->_health > this->_max_health) {
            this->_health = this->_max_health;
        }

        if (this->_health < 0) {
            this->_on_death_event.invoke(this->get_entity());
        }
    }

    inline void health(int health) { this->_health = health < this->_max_health ? health : this->_max_health; }

    inline int health() const { return this->_health; }

    inline bool is_alive() const { return this->_health > 0; }

    inline void max_health(int max_health) { this->_max_health = max_health; }

    inline int max_health() { return this->_max_health; }

    inline Handle<DeathEvent> get_on_death_event() { return this->_on_death_event.make_handle<DeathEvent>(); }

   protected:
    inline Handle<TransformComponent> transform_component() { return this->_transform_component; }

    inline Handle<PhysicsComponent> physics_component() { return this->_physics_component; }

    inline Handle<WalkingAnimationComponent> walking_animation_component() {
        return this->_walking_animation_component;
    }

   private:
    void _move(CharacterComponent &&other);

   private:
    int _health;
    int _max_health;
    Handle<TransformComponent> _transform_component;
    Handle<PhysicsComponent> _physics_component;
    Handle<WalkingAnimationComponent> _walking_animation_component;
    DeathEvent _on_death_event;
};
