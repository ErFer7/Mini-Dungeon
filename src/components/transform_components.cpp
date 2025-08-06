#include "../../include/components/transform_component.hpp"
#include "../../include/entities/entity.hpp"
#include "raylib.h"
#include "raymath.h"
#include "utils/transform.hpp"

TransformComponent::TransformComponent(GameCore *game_core, Entity *entity) : Component(game_core, entity, true) {
    this->_transform_system = TransformSystem();
}

void TransformComponent::set_position(Vector2 position) {
    Vector2 old_position = this->_transform_system.get_absolute_position();
    Vector2 diff_position = Vector2Subtract(position, old_position);
    Transform2D diff_transform = Transform2D(diff_position, 0.0f, Vector2One());

    this->_transform_system.set_absolute_position(position);
    this->_on_update_event.invoke(position, diff_transform);
}

void TransformComponent::set_rotation(float rotation) {
    float old_rotation = this->_transform_system.get_absolute_rotation();
    float diff_rotation = rotation - old_rotation;
    Transform2D diff_transform = Transform2D(Vector2Zero(), diff_rotation, Vector2One());

    this->_transform_system.set_absolute_rotation(rotation);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void TransformComponent::set_scale(Vector2 scale) {
    Vector2 old_scale = this->_transform_system.get_absolute_scale();
    Vector2 diff_scale = Vector2Divide(scale, old_scale);
    Transform2D diff_transform = Transform2D(Vector2Zero(), 0.0f, diff_scale);

    this->_transform_system.set_absolute_scale(scale);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void TransformComponent::translate(Vector2 translation) {
    Transform2D diff_transform = Transform2D(translation, 0.0f, Vector2One());

    this->_transform_system.translate(translation);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void TransformComponent::rotate(float rotation) {
    Transform2D diff_transform = Transform2D(Vector2Zero(), rotation, Vector2One());
    Vector2 origin = this->_transform_system.get_absolute_position();

    this->_transform_system.rotate(origin, rotation);
    this->_on_update_event.invoke(origin, diff_transform);
}

void TransformComponent::scale(Vector2 scale) {
    Transform2D diff_transform = Transform2D(Vector2Zero(), 0.0f, scale);
    Vector2 origin = this->_transform_system.get_absolute_position();

    this->_transform_system.scale(origin, scale);
    this->_on_update_event.invoke(origin, diff_transform);
}
