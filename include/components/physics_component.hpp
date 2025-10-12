#pragma once

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
   public:
    PhysicsComponent(GameCore *game_core, Entity *entity, const PhysicsComponentArgs &args = PhysicsComponentArgs());

    ~PhysicsComponent() override;

    inline Vector2Df get_velocity() const { return this->_velocity; }

    void set_velocity(Vector2Df velocity) { this->_velocity = velocity; }

    inline Vector2Df get_acceleration() const { return this->_acceleration; }

    inline void set_acceleration(Vector2Df acceleration) { this->_acceleration = acceleration; }

    inline float get_drag() { return this->_drag; }

    inline void set_drag(float drag) { this->_drag = drag; }

    void update();

   protected:
    void register_component() override;

    void unregister_component() override;

   private:
    // TODO: Model force and mass
    Vector2Df _velocity;
    Vector2Df _acceleration;
    float _drag;  // This is more of a "logical" drag that is applied in order to force objects to slow down
    double _time;
    TransformComponent *_transform_component;
};
