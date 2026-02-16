#pragma once

#include "components/collider_component.hpp"
#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "managers/physics_component_manager.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct PhysicsComponentArgs {
    Vector2Df initial_velocity = Vector2Df();
    Vector2Df initial_acceleration = Vector2Df();
    float drag = 1.0f;
};

class PhysicsComponent final : public Component {
    friend class ColliderComponent;
    friend class PhysicsComponentManager;

   public:
    PhysicsComponent(Handle<Entity> entity, const PhysicsComponentArgs &args = PhysicsComponentArgs());

    PhysicsComponent(PhysicsComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~PhysicsComponent() override = default;

    PhysicsComponent &operator=(PhysicsComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Vector2Df get_velocity() const { return this->_velocity; }

    inline void set_velocity(Vector2Df velocity) {
        this->_velocity = velocity;
        this->_is_statically_stable = false;
    }

    inline void set_velocity_x(float velocity_x) {
        this->_velocity.x = velocity_x;
        this->_is_statically_stable = false;
    }

    inline void set_velocity_y(float velocity_y) {
        this->_velocity.y = velocity_y;
        this->_is_statically_stable = false;
    }

    inline Vector2Df get_acceleration() const { return this->_acceleration; }

    inline void set_acceleration(Vector2Df acceleration) {
        this->_acceleration = acceleration;
        this->_is_statically_stable = false;
    }

    inline void set_acceleration_x(float acceleration_x) {
        this->_acceleration.x = acceleration_x;
        this->_is_statically_stable = false;
    }

    inline void set_acceleration_y(float acceleration_y) {
        this->_acceleration.y = acceleration_y;
        this->_is_statically_stable = false;
    }

    inline float get_drag() { return this->_drag; }

    inline void set_drag(float drag) { this->_drag = drag; }

    // Returns true when the component is stopped for two consecutive frames.
    inline bool is_statically_stable() const { return this->_is_statically_stable; }

    inline bool is_colliding() const { return this->_is_colliding; }

    void update();

    inline void set_collider_component(Handle<ColliderComponent> collider_component) {
        this->_collider_component = collider_component;
    }

    inline void set_is_colliding(bool is_colliding) {
        this->_is_colliding = is_colliding;
        this->_is_statically_stable = !is_colliding;
    }

    // Bypass for the PhysicsComponentManager
    inline Handle<TransformComponent> get_transform_component() const { return this->_transform_component; }

    // Bypass for the PhysicsComponentManager
    inline Handle<ColliderComponent> get_collider_component() const { return this->_collider_component; }

   private:
    void _move(PhysicsComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_velocity = std::move(other._velocity);
        this->_acceleration = std::move(other._acceleration);
        this->_drag = std::move(other._drag);
        this->_time = std::move(other._time);
        this->_is_statically_stable = std::move(other._is_statically_stable);
        this->_is_colliding = std::move(other._is_colliding);
        this->_transform_component = std::move(other._transform_component);
        this->_collider_component = std::move(other._collider_component);
    }

   private:
    // TODO: Model force and mass
    Vector2Df _velocity;
    Vector2Df _acceleration;
    float _drag;  // This is more of a "logical" drag that is applied in order to force objects to slow down
    double _time;
    // This is used for checking the movement state without checking if the velocity and acceleration are 0
    bool _is_statically_stable;
    bool _is_colliding;
    utils::Handle<TransformComponent> _transform_component;
    utils::Handle<ColliderComponent> _collider_component;
};
