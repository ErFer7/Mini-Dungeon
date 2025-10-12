#pragma once

#include "components/collider_component.hpp"
#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct PhysicsComponentArgs {
    Vector2Df initial_velocity = Vector2Df();
    Vector2Df initial_acceleration = Vector2Df();
    float drag = 1.0f;
};

class PhysicsComponent : public Component {
    friend class ColliderComponent;

   public:
    PhysicsComponent(GameCore *game_core, Entity *entity, const PhysicsComponentArgs &args = PhysicsComponentArgs());

    ~PhysicsComponent() override;

    inline Vector2Df get_velocity() const { return this->_velocity; }

    inline void set_velocity(Vector2Df velocity) { this->_velocity = velocity; }

    inline void set_velocity_x(float velocity_x) { this->_velocity.x = velocity_x; }

    inline void set_velocity_y(float velocity_y) { this->_velocity.y = velocity_y; }

    inline Vector2Df get_acceleration() const { return this->_acceleration; }

    inline void set_acceleration(Vector2Df acceleration) { this->_acceleration = acceleration; }

    inline void set_acceleration_x(float acceleration_x) { this->_acceleration.x = acceleration_x; }

    inline void set_acceleration_y(float acceleration_y) { this->_acceleration.y = acceleration_y; }

    inline float get_drag() { return this->_drag; }

    inline void set_drag(float drag) { this->_drag = drag; }

    void update();

   protected:
    void register_component() override;

    void unregister_component() override;

    inline void set_collider_component(ColliderComponent *collider_component) {
        this->_collider_component = collider_component;
    }

   private:
    // TODO: Model force and mass
    Vector2Df _velocity;
    Vector2Df _acceleration;
    float _drag;  // This is more of a "logical" drag that is applied in order to force objects to slow down
    double _time;
    TransformComponent *_transform_component;
    ColliderComponent *_collider_component;
};
