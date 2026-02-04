#pragma once

#include "components/component.hpp"
#include "utils/transform.hpp"

using utils::TransformData;
using utils::Vector2Df;

struct TransformComponentArgs {
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
};

class TransformComponent final : public Component {
   public:
    typedef Event<Vector2Df, TransformData> TransformUpdateEvent;
    typedef TransformUpdateEvent::Listener TransformUpdateListener;

   public:
    TransformComponent(GameCore *game_core,
                       Entity *entity,
                       const TransformComponentArgs &args = TransformComponentArgs{});

    ~TransformComponent() override = default;

    inline Vector2Df get_position() const { return this->_transform.get_position(); }

    inline float get_rotation() const { return this->_transform.get_rotation(); }

    inline Vector2Df get_scale() const { return this->_transform.get_scale(); }

    inline TransformUpdateEvent *get_on_update_event() { return &this->_on_update_event; }

    void set_position(Vector2Df position);

    void set_rotation(float rotation);

    void set_scale(Vector2Df scale);

    inline Vector2Df get_relative_position(Vector2Df origin_position) const {
        return this->_transform.get_relative_position(origin_position);
    }

    inline float get_relative_rotation(float origin_rotation) const {
        return this->_transform.get_relative_rotation(origin_rotation);
    }

    inline Vector2Df get_relative_scale(Vector2Df origin_scale) const {
        return this->_transform.get_relative_scale(origin_scale);
    }

    void set_relative_position(Vector2Df origin, Vector2Df position);

    void set_relative_rotation(Vector2Df origin, float origin_rotation, float rotation);

    void set_relative_scale(Vector2Df origin, Vector2Df origin_scale, Vector2Df scale);

    void translate(Vector2Df translation);

    void rotate(float rotation);

    void scale(Vector2Df scale);

   private:
    utils::Transform _transform;
    TransformUpdateEvent _on_update_event;
};
