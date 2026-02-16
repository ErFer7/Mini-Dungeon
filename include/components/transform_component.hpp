#pragma once

#include "components/component.hpp"
#include "utils/transform.hpp"

using utils::Handle;
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
    TransformComponent(Handle<Entity> entity, const TransformComponentArgs &args = TransformComponentArgs{});

    TransformComponent(TransformComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~TransformComponent() override = default;

    TransformComponent &operator=(TransformComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Vector2Df get_position() const { return this->_transform.get_position(); }

    inline float get_rotation() const { return this->_transform.get_rotation(); }

    inline Vector2Df get_scale() const { return this->_transform.get_scale(); }

    inline Handle<TransformUpdateEvent> get_on_update_event() {
        return Handle<TransformUpdateEvent>(this->_on_update_event.get_id());
    }

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
    void _move(TransformComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_transform = std::move(other._transform);
        this->_on_update_event = std::move(other._on_update_event);
    }

   private:
    // TODO: Check if utils:: is necessary here
    utils::Transform _transform;
    TransformUpdateEvent _on_update_event;
};
