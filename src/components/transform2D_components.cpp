#include "../../include/components/transform2D_component.hpp"
#include "../../include/entities/entity.hpp"
#include "raylib.h"
#include "raymath.h"
#include "utils/transform.hpp"

Transform2DComponent::Transform2DComponent(EngineCore *engine_core, Entity *entity) : Component(engine_core, entity, true) {
    this->_transform_system = TransformSystem2D();
    this->_on_parent_transform_update_listener = TransformUpdateListener([this](const Vector2 &origin, const Transform2D &diff_transform) {
        this->_transform_system.translate(diff_transform.position);
        this->_transform_system.rotate(origin, diff_transform.rotation);
        this->_transform_system.scale(origin, diff_transform.scale);

        this->_on_update_event.invoke(origin, diff_transform);
    });

    this->_parent_transform = this->get_entity()->get_parent()->get_component<Transform2DComponent>();

    if (this->_parent_transform != nullptr) {
        this->_on_parent_transform_update_listener.subscribe(this->_parent_transform->get_on_update_event());
    }
}

void Transform2DComponent::set_position(Vector2 position) {
    Vector2 old_position = this->_transform_system.get_absolute_position();
    Vector2 diff_position = Vector2Subtract(position, old_position);
    Transform2D diff_transform = Transform2D(diff_position, 0.0f, Vector2One());

    this->_transform_system.set_absolute_position(position);
    this->_on_update_event.invoke(position, diff_transform);
}

void Transform2DComponent::set_rotation(float rotation) {
    float old_rotation = this->_transform_system.get_absolute_rotation();
    float diff_rotation = rotation - old_rotation;
    Transform2D diff_transform = Transform2D(Vector2Zero(), diff_rotation, Vector2One());

    this->_transform_system.set_absolute_rotation(rotation);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::set_scale(Vector2 scale) {
    Vector2 old_scale = this->_transform_system.get_absolute_scale();
    Vector2 diff_scale = Vector2Divide(scale, old_scale);
    Transform2D diff_transform = Transform2D(Vector2Zero(), 0.0f, diff_scale);

    this->_transform_system.set_absolute_scale(scale);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::set_relative_position(Vector2 position) {
    Vector2 parent_position = this->_parent_transform->get_position();
    Vector2 old_position = this->_transform_system.get_relative_position(parent_position);
    Vector2 diff = Vector2Subtract(position, old_position);
    Transform2D diff_transform = Transform2D(diff, 0.0f, Vector2One());

    this->_transform_system.set_relative_position(parent_position, position);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::set_relative_rotation(float rotation) {
    float parent_rotation = this->_parent_transform->get_rotation();
    float old_rotation = this->_transform_system.get_relative_rotation(parent_rotation);
    float diff_rotation = rotation - old_rotation;
    Transform2D diff_transform = Transform2D(Vector2Zero(), diff_rotation, Vector2One());

    this->_transform_system.set_relative_rotation(this->_parent_transform->get_position(), parent_rotation, rotation);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::set_relative_scale(Vector2 scale) {
    Vector2 parent_scale = this->_parent_transform->get_scale();
    Vector2 old_scale = this->_transform_system.get_relative_scale(parent_scale);
    Vector2 diff_scale = Vector2Divide(scale, old_scale);
    Transform2D diff_transform = Transform2D(Vector2Zero(), 0.0f, diff_scale);

    this->_transform_system.set_relative_scale(this->_parent_transform->get_position(), parent_scale, scale);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::translate(Vector2 translation) {
    Transform2D diff_transform = Transform2D(translation, 0.0f, Vector2One());

    this->_transform_system.translate(translation);
    this->_on_update_event.invoke(this->_transform_system.get_absolute_position(), diff_transform);
}

void Transform2DComponent::rotate(float rotation) {
    Transform2D diff_transform = Transform2D(Vector2Zero(), rotation, Vector2One());
    Vector2 origin = this->_transform_system.get_absolute_position();

    this->_transform_system.rotate(origin, rotation);
    this->_on_update_event.invoke(origin, diff_transform);
}

void Transform2DComponent::scale(Vector2 scale) {
    Transform2D diff_transform = Transform2D(Vector2Zero(), 0.0f, scale);
    Vector2 origin = this->_transform_system.get_absolute_position();

    this->_transform_system.scale(origin, scale);
    this->_on_update_event.invoke(origin, diff_transform);
}
