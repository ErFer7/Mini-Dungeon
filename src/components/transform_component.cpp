#include "components/transform_component.hpp"

#include "entities/entity.hpp"
#include "utils/transform_data.hpp"
#include "utils/vector.hpp"

TransformComponent::TransformComponent(Entity *entity, const TransformComponentArgs &args) : Component(entity) {
    utils::log_trace(this, __PRETTY_FUNCTION__, entity);

    this->_transform = utils::Transform(args.position, args.rotation, args.scale);
}

void TransformComponent::set_position(Vector2Df position) {
    if (this->_on_update_event.has_listeners()) {
        Vector2Df old_position = this->_transform.get_position();
        Vector2Df diff_position = position - old_position;
        TransformData diff_transform = TransformData(diff_position, 0.0f, Vector2Df(1.0f));

        this->_transform.set_position(position);
        this->_on_update_event.invoke(position, diff_transform);
    } else {
        this->_transform.set_position(position);
    }
}

void TransformComponent::set_rotation(float rotation) {
    if (this->_on_update_event.has_listeners()) {
        float old_rotation = this->_transform.get_rotation();
        float diff_rotation = rotation - old_rotation;
        TransformData diff_transform = TransformData(Vector2Df(), diff_rotation, Vector2Df(1.0f));

        this->_transform.set_rotation(rotation);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_rotation(rotation);
    }
}

void TransformComponent::set_scale(Vector2Df scale) {
    if (this->_on_update_event.has_listeners()) {
        Vector2Df old_scale = this->_transform.get_scale();
        Vector2Df diff_scale = scale / old_scale;
        TransformData diff_transform = TransformData(Vector2Df(), 0.0f, diff_scale);

        this->_transform.set_scale(scale);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_scale(scale);
    }
}

void TransformComponent::set_relative_position(Vector2Df origin, Vector2Df position) {
    if (this->_on_update_event.has_listeners()) {
        Vector2Df old_position = this->_transform.get_relative_position(origin);
        Vector2Df diff = position - old_position;
        TransformData diff_transform = TransformData(diff, 0.0f, Vector2Df(1.0f));

        this->_transform.set_relative_position(origin, position);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_relative_position(origin, position);
    }
}

void TransformComponent::set_relative_rotation(Vector2Df origin, float origin_rotation, float rotation) {
    if (this->_on_update_event.has_listeners()) {
        float old_rotation = this->_transform.get_relative_rotation(origin_rotation);
        float diff_rotation = rotation - old_rotation;
        TransformData diff_transform = TransformData(Vector2Df(), diff_rotation, Vector2Df(1.0f));

        this->_transform.set_relative_rotation(origin, origin_rotation, rotation);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_relative_rotation(origin, origin_rotation, rotation);
    }
}

void TransformComponent::set_relative_scale(Vector2Df origin, Vector2Df origin_scale, Vector2Df scale) {
    if (this->_on_update_event.has_listeners()) {
        Vector2Df old_scale = this->_transform.get_relative_scale(origin_scale);
        Vector2Df diff_scale = scale - old_scale;
        TransformData diff_transform = TransformData(Vector2Df(), 0.0f, diff_scale);

        this->_transform.set_relative_scale(origin, origin_scale, scale);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_relative_scale(origin, origin_scale, scale);
    }
}

void TransformComponent::translate(Vector2Df translation) {
    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(translation, 0.0f, Vector2Df(1.0f));

        this->_transform.translate(translation);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.translate(translation);
    }
}

void TransformComponent::rotate(float rotation) {
    Vector2Df origin = this->_transform.get_position();

    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(Vector2Df(), rotation, Vector2Df(1.0f));

        this->_transform.rotate(origin, rotation);
        this->_on_update_event.invoke(origin, diff_transform);
    } else {
        this->_transform.rotate(origin, rotation);
    }
}

void TransformComponent::scale(Vector2Df scale) {
    Vector2Df origin = this->_transform.get_position();

    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(Vector2Df(), 0.0f, scale);

        this->_transform.scale(origin, scale);
        this->_on_update_event.invoke(origin, diff_transform);
    } else {
        this->_transform.scale(origin, scale);
    }
}
