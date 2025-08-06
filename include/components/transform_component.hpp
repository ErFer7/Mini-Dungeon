#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform_system.hpp"
#include "component.hpp"
#include "raylib.h"
#include "utils/transform.hpp"

class TransformComponent : public Component {
   public:
    typedef Event<Vector2, Transform2D> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

   public:
    TransformComponent(GameCore *game_core, Entity *entity);

    ~TransformComponent() override { this->unregister_component(); };

    inline Transform2D get_transform() const { return this->_transform_system.get_absolute(); }

    inline Vector2 get_position() const { return this->_transform_system.get_absolute_position(); }

    inline float get_rotation() const { return this->_transform_system.get_absolute_rotation(); }

    inline Vector2 get_scale() const { return this->_transform_system.get_absolute_scale(); }

    inline TransformUpdateEvent *get_on_update_event() { return &this->_on_update_event; }

    void set_position(Vector2 position);

    void set_rotation(float rotation);

    void set_scale(Vector2 scale);

    void translate(Vector2 translation);

    void rotate(float rotation);

    void scale(Vector2 scale);

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    TransformSystem _transform_system;
    TransformUpdateEvent _on_update_event;
};