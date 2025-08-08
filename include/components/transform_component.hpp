#pragma once

#include "../types.hpp"
#include "../utils/event.hpp"
#include "../utils/transform.hpp"
#include "../utils/transform_data.hpp"
#include "component.hpp"

using utils::TransformData;

class TransformComponent : public Component {
   public:
    typedef Event<Vector2, TransformData> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

   public:
    TransformComponent(GameCore *game_core, Entity *entity);

    ~TransformComponent() override { this->unregister_component(); };

    inline utils::Transform get_transform() const { return this->_transform; }

    inline Vector2 get_position() const { return this->_transform.get_position(); }

    inline float get_rotation() const { return this->_transform.get_rotation(); }

    inline Vector2 get_scale() const { return this->_transform.get_scale(); }

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
    utils::Transform _transform;
    TransformUpdateEvent _on_update_event;
};
