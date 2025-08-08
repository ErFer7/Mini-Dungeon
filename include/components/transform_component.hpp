#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform.hpp"
#include "../utils/transform_data.hpp"
#include "component.hpp"
#include "raylib.h"

using utils::TransformData;

class TransformComponent : public Component {
   public:
    typedef Event<Vector2, TransformData> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

   public:
    TransformComponent(GameCore *game_core, Entity *entity);

    ~TransformComponent() override { this->unregister_component(); };

    inline Vector2 get_position() const { return this->_transform.get_position(); }

    inline float get_rotation() const { return this->_transform.get_rotation(); }

    inline Vector2 get_scale() const { return this->_transform.get_scale(); }

    inline TransformUpdateEvent *get_on_update_event() { return &this->_on_update_event; }

    void set_position(Vector2 position);

    void set_rotation(float rotation);

    void set_scale(Vector2 scale);

    inline Vector2 get_relative_position(Vector2 origin_position) const { return this->_transform.get_relative_position(origin_position); }

    inline float get_relative_rotation(float origin_rotation) const { return this->_transform.get_relative_rotation(origin_rotation); }

    inline Vector2 get_relative_scale(Vector2 origin_scale) const { return this->_transform.get_relative_scale(origin_scale); }

    void set_relative_position(Vector2 origin, Vector2 position);

    void set_relative_rotation(Vector2 origin, float origin_rotation, float rotation);

    void set_relative_scale(Vector2 origin, Vector2 origin_scale, Vector2 scale);

    void translate(Vector2 translation);

    void rotate(float rotation);

    void scale(Vector2 scale);

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    utils::Transform _transform;
    TransformUpdateEvent _on_update_event;
};
