#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform_system2D.hpp"
#include "component.hpp"
#include "raylib.h"
#include "utils/transform.hpp"

class Transform2DComponent : public Component {
   public:
    typedef Event<Vector2, Transform2D> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

    Transform2DComponent(EngineCore *engine_core, Entity *entity);

    ~Transform2DComponent() override { this->unregister_component(); };

    inline Transform2D get_transform() const { return this->_transform_system.get_absolute(); }

    inline Vector2 get_position() const { return this->_transform_system.get_absolute_position(); }

    inline float get_rotation() const { return this->_transform_system.get_absolute_rotation(); }

    inline Vector2 get_scale() const { return this->_transform_system.get_absolute_scale(); }

    inline Transform2D get_relative_transform() const {
        return this->_transform_system.get_relative(this->_parent_transform->get_transform());
    }

    inline Vector2 get_relative_position() const { return this->get_relative_transform().position; }

    inline float get_relative_rotation() const { return this->get_relative_transform().rotation; }

    inline Vector2 get_relative_scale() const { return this->get_relative_transform().scale; }

    inline TransformUpdateEvent *get_on_update_event() { return &this->_on_update_event; }

    void set_position(Vector2 position);

    void set_rotation(float rotation);

    void set_scale(Vector2 scale);

    void set_relative_position(Vector2 position);

    void set_relative_rotation(float rotation);

    void set_relative_scale(Vector2 scale);

    void translate(Vector2 translation);

    void rotate(float rotation);

    void scale(Vector2 scale);

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    TransformSystem2D _transform_system;
    TransformUpdateEvent _on_update_event;
    TransformUpdateListener _on_parent_transform_update_listener;
    Transform2DComponent *_parent_transform;
};