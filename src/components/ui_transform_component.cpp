#include "../../include/components/ui_transform_component.hpp"

#include "../../include/entities/entity.hpp"
#include "raylib.h"
#include "raymath.h"

UITransformComponent::UITransformComponent(GameCore *game_core,
                                           Entity *entity,
                                           UIOrigin ui_origin,
                                           UITransformComponent *parent_ui_transform)
    : Component(game_core, entity, true) {
    this->_ui_origin = ui_origin;
    this->_parent_ui_transform = parent_ui_transform;

    if (this->_parent_ui_transform != nullptr) {
        Entity *parent = this->_parent_ui_transform->get_entity();
        this->_parent_transform_component = parent->get_component<TransformComponent>();
        this->_parent_graphics_component = parent->get_component<GraphicsComponent>();
    } else {
        this->_parent_transform_component = nullptr;
        this->_parent_graphics_component = nullptr;
    }

    this->_transform_component = entity->get_component<TransformComponent>();
    this->_graphics_component = entity->get_component<GraphicsComponent>();
}

Vector2 UITransformComponent::get_position() const { return Vector2Subtract(this->_get_anchor_point(), this->_get_origin()); }

void UITransformComponent::set_position(Vector2 position) {
    Vector2 origin = this->_get_origin();
    Vector2 diff = Vector2Add(origin, position);
    Rectangle rect = this->_graphics_component->get_rectangle();
    Vector2 calculated_position;

    switch (this->_ui_origin) {
        case UIOrigin::TOP_LEFT:
            calculated_position = Vector2{diff.x + rect.width / 2.0f, diff.y + rect.height / 2.0f};
            break;
        case UIOrigin::TOP:
            calculated_position = Vector2{diff.x, diff.y + rect.height / 2.0f};
            break;
        case UIOrigin::TOP_RIGHT:
            calculated_position = Vector2{diff.x - rect.width / 2.0f, diff.y + rect.height / 2.0f};
            break;
        case UIOrigin::LEFT:
            calculated_position = Vector2{diff.x + rect.width / 2.0f, diff.y};
            break;
        case UIOrigin::CENTER:
            calculated_position = diff;
            break;
        case UIOrigin::RIGHT:
            calculated_position = Vector2{diff.x - rect.width / 2.0f, diff.y};
            break;
        case UIOrigin::BOTTOM_LEFT:
            calculated_position = Vector2{diff.x + rect.width / 2.0f, diff.y - rect.height / 2.0f};
            break;
        case UIOrigin::BOTTOM:
            calculated_position = Vector2{diff.x, diff.y - rect.height / 2.0f};
            break;
        case UIOrigin::BOTTOM_RIGHT:
            calculated_position = Vector2{diff.x - rect.width / 2.0f, diff.y - rect.height / 2.0f};
            break;
    }

    this->_transform_component->set_position(calculated_position);
}

void UITransformComponent::set_rotation(float rotation) {
    Vector2 origin;
    float origin_rotation;

    if (this->_parent_graphics_component != nullptr) {
        origin = this->_parent_transform_component->get_position();
        origin_rotation = this->_parent_transform_component->get_rotation();
    } else {
        origin = Vector2Zero();
        origin_rotation = 0.0f;
    }

    // TODO: Fix the access, this won't work
    this->_transform_component->get_transform().set_relative_rotation(origin, origin_rotation, rotation);
}

void UITransformComponent::set_scale(Vector2 scale) {
    Vector2 origin;
    Vector2 origin_scale;

    if (this->_parent_graphics_component != nullptr) {
        origin = this->_parent_transform_component->get_position();
        origin_scale = this->_parent_transform_component->get_scale();
    } else {
        origin = Vector2Zero();
        origin_scale = Vector2Zero();
    }

    this->_transform_component->get_transform().set_relative_scale(origin, origin_scale, scale);
}

Vector2 UITransformComponent::_get_origin() const {
    Rectangle base_rect;

    if (this->_parent_graphics_component != nullptr) {
        base_rect = this->_parent_graphics_component->get_rectangle();
    } else {
        base_rect = Rectangle{0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
    }

    return this->_rect_point_by_ui_origin(base_rect);
}

Vector2 UITransformComponent::_get_anchor_point() const {
    return this->_rect_point_by_ui_origin(this->_graphics_component->get_rectangle());
}

Vector2 UITransformComponent::_rect_point_by_ui_origin(Rectangle rectangle) const {
    switch (this->_ui_origin) {
        case UIOrigin::TOP_LEFT:
            return Vector2{rectangle.x, rectangle.y};
        case UIOrigin::TOP:
            return Vector2{rectangle.x + rectangle.width / 2.0f, rectangle.y};
        case UIOrigin::TOP_RIGHT:
            return Vector2{rectangle.x + rectangle.width, rectangle.y};
        case UIOrigin::LEFT:
            return Vector2{rectangle.x, rectangle.y + rectangle.height / 2.0f};
        case UIOrigin::CENTER:
            return Vector2{rectangle.x + rectangle.width / 2.0f, rectangle.y + rectangle.height / 2.0f};
        case UIOrigin::RIGHT:
            return Vector2{rectangle.x + rectangle.width, rectangle.y + rectangle.height / 2.0f};
        case UIOrigin::BOTTOM_LEFT:
            return Vector2{rectangle.x, rectangle.y + rectangle.height};
        case UIOrigin::BOTTOM:
            return Vector2{rectangle.x + rectangle.width / 2.0f, rectangle.y + rectangle.height};
        case UIOrigin::BOTTOM_RIGHT:
            return Vector2{rectangle.x + rectangle.width, rectangle.y + rectangle.height};
    }

    return Vector2Zero();
}
