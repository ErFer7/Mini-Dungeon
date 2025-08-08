#include "../../include/components/transform_component.hpp"
#include "../../include/entities/entity.hpp"
#include "raylib.h"
#include "raymath.h"

TransformComponent::TransformComponent(GameCore *game_core, Entity *entity) : Component(game_core, entity, true) {
    this->_transform = utils::Transform();
}

void TransformComponent::set_position(Vector2 position) {
    if (this->_on_update_event.has_listeners()) {
        Vector2 old_position = this->_transform.get_position();
        Vector2 diff_position = Vector2Subtract(position, old_position);
        TransformData diff_transform = TransformData(diff_position, 0.0f, Vector2One());

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
        TransformData diff_transform = TransformData(Vector2Zero(), diff_rotation, Vector2One());

        this->_transform.set_rotation(rotation);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_rotation(rotation);
    }
}

void TransformComponent::set_scale(Vector2 scale) {
    if (this->_on_update_event.has_listeners()) {
        Vector2 old_scale = this->_transform.get_scale();
        Vector2 diff_scale = Vector2Divide(scale, old_scale);
        TransformData diff_transform = TransformData(Vector2Zero(), 0.0f, diff_scale);

        this->_transform.set_scale(scale);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.set_scale(scale);
    }
}

void TransformComponent::translate(Vector2 translation) {
    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(translation, 0.0f, Vector2One());

        this->_transform.translate(translation);
        this->_on_update_event.invoke(this->_transform.get_position(), diff_transform);
    } else {
        this->_transform.translate(translation);
    }
}

void TransformComponent::rotate(float rotation) {
    Vector2 origin = this->_transform.get_position();

    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(Vector2Zero(), rotation, Vector2One());

        this->_transform.rotate(origin, rotation);
        this->_on_update_event.invoke(origin, diff_transform);
    } else {
        this->_transform.rotate(origin, rotation);
    }
}

void TransformComponent::scale(Vector2 scale) {
    Vector2 origin = this->_transform.get_position();

    if (this->_on_update_event.has_listeners()) {
        TransformData diff_transform = TransformData(Vector2Zero(), 0.0f, scale);

        this->_transform.scale(origin, scale);
        this->_on_update_event.invoke(origin, diff_transform);
    } else {
        this->_transform.scale(origin, scale);
    }
}
