#include "components/ui_transform_component.hpp"

#include <raylib.h>

#include "entities/entity.hpp"
#include "game_core.hpp"
#include "utils/debug.hpp"
#include "utils/vector.hpp"

using utils::log_info;

UITransformComponent::UITransformComponent(Handle<Entity> entity, const UITransformComponentArgs &args)
    : Component(entity),
      _ui_origin(args.ui_origin),
      _parent_ui_transform(args.parent_ui_transform),
      _parent_transform_component(),
      _parent_graphics_component() {
    log_trace(this, __PRETTY_FUNCTION__, entity);

    if (!this->_parent_ui_transform.is_null()) {
        log_info(this, "UITransformComponent: Using ", this->_parent_ui_transform, " as parent");

        Handle<Entity> parent = this->_parent_ui_transform->get_entity();
        this->_parent_transform_component = parent->get_component<TransformComponent>();
        this->_parent_graphics_component = parent->get_component<GraphicsComponent>();
    } else {
        log_info(this, "UITransformComponent: Using screen as parent");

        this->_screen_resize_listener
            .bind_callable<UITransformComponent, &UITransformComponent::_screen_resize_listener_call>(
                this->make_handle<UITransformComponent>());
        this->_screen_resize_listener.subscribe(GameCore::get_graphics_manager()->get_on_screen_resize_event());
    }

    this->_transform_component = entity->get_component<TransformComponent>();
    this->_graphics_component = entity->get_component<GraphicsComponent>();

    if (!this->_parent_graphics_component.is_null()) {
        this->_graphics_component->set_layer(this->_parent_graphics_component->get_layer() + 1);
        this->_base_rectangle = this->_graphics_component->get_rectangle();
    } else {
        this->_base_rectangle =
            Rectangle{0.0f, 0.0f, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
    }

    // TODO: Improve the "clean code"
    // TODO: Implement set methods that don't emit events, thus avoiding multiple event invocations
    this->set_position(args.position);
    this->set_rotation(args.rotation);
    this->set_scale(args.scale);
}

Vector2Df UITransformComponent::get_position() const { return this->_get_anchor_point() - this->_get_origin(); }

void UITransformComponent::set_position(Vector2Df position) {
    Vector2Df origin = this->_get_origin();
    Vector2Df diff = origin + position;
    Rectangle rect = this->_graphics_component->get_rectangle();
    Vector2Df calculated_position;

    switch (this->_ui_origin) {
        case UIOrigin::TOP_LEFT:
            calculated_position = Vector2Df(diff.x + rect.width / 2.0f, diff.y + rect.height / 2.0f);
            break;
        case UIOrigin::TOP:
            calculated_position = Vector2Df(diff.x, diff.y + rect.height / 2.0f);
            break;
        case UIOrigin::TOP_RIGHT:
            calculated_position = Vector2Df(diff.x - rect.width / 2.0f, diff.y + rect.height / 2.0f);
            break;
        case UIOrigin::LEFT:
            calculated_position = Vector2Df(diff.x + rect.width / 2.0f, diff.y);
            break;
        case UIOrigin::CENTER:
            calculated_position = diff;
            break;
        case UIOrigin::RIGHT:
            calculated_position = Vector2Df(diff.x - rect.width / 2.0f, diff.y);
            break;
        case UIOrigin::BOTTOM_LEFT:
            calculated_position = Vector2Df(diff.x + rect.width / 2.0f, diff.y - rect.height / 2.0f);
            break;
        case UIOrigin::BOTTOM:
            calculated_position = Vector2Df(diff.x, diff.y - rect.height / 2.0f);
            break;
        case UIOrigin::BOTTOM_RIGHT:
            calculated_position = Vector2Df(diff.x - rect.width / 2.0f, diff.y - rect.height / 2.0f);
            break;
    }

    this->_transform_component->set_position(calculated_position);
}

void UITransformComponent::set_rotation(float rotation) {
    Vector2Df origin;
    float origin_rotation;

    if (!this->_parent_transform_component.is_null()) {
        origin = this->_parent_transform_component->get_position();
        origin_rotation = this->_parent_transform_component->get_rotation();
    } else {
        origin = this->_transform_component->get_position();
        origin_rotation = 0.0f;
    }

    this->_transform_component->set_relative_rotation(origin, origin_rotation, rotation);
}

void UITransformComponent::set_scale(Vector2Df scale) {
    Vector2Df origin;
    Vector2Df origin_scale;

    if (!this->_parent_transform_component.is_null()) {
        origin = this->_parent_transform_component->get_position();
        origin_scale = this->_parent_transform_component->get_scale();
    } else {
        origin = this->_transform_component->get_position();
        origin_scale = Vector2Df(1.0f);
    }

    this->_transform_component->set_relative_scale(origin, origin_scale, scale);
}

void UITransformComponent::translate(Vector2Df translation) { this->_transform_component->translate(translation); }

void UITransformComponent::rotate(float rotation) { this->_transform_component->rotate(rotation); }

void UITransformComponent::scale(Vector2Df scale) { this->_transform_component->scale(scale); }

void UITransformComponent::_move(UITransformComponent &&other) {
    if (this == &other) {
        return;
    }

    this->_ui_origin = std::move(other._ui_origin);
    this->_base_rectangle = std::move(other._base_rectangle);
    this->_parent_ui_transform = std::move(other._parent_ui_transform);
    this->_parent_transform_component = std::move(other._parent_transform_component);
    this->_parent_graphics_component = std::move(other._parent_graphics_component);
    this->_transform_component = std::move(other._transform_component);
    this->_graphics_component = std::move(other._graphics_component);
    this->_screen_resize_listener = std::move(other._screen_resize_listener);
}

Vector2Df UITransformComponent::_get_origin() const { return this->_rect_point_by_ui_origin(this->_base_rectangle); }

Vector2Df UITransformComponent::_get_anchor_point() const {
    return this->_rect_point_by_ui_origin(this->_graphics_component->get_rectangle());
}

Vector2Df UITransformComponent::_rect_point_by_ui_origin(Rectangle rectangle) const {
    switch (this->_ui_origin) {
        case UIOrigin::TOP_LEFT:
            return Vector2Df(rectangle.x, rectangle.y);
        case UIOrigin::TOP:
            return Vector2Df(rectangle.x + rectangle.width / 2.0f, rectangle.y);
        case UIOrigin::TOP_RIGHT:
            return Vector2Df(rectangle.x + rectangle.width, rectangle.y);
        case UIOrigin::LEFT:
            return Vector2Df(rectangle.x, rectangle.y + rectangle.height / 2.0f);
        case UIOrigin::CENTER:
            return Vector2Df(rectangle.x + rectangle.width / 2.0f, rectangle.y + rectangle.height / 2.0f);
        case UIOrigin::RIGHT:
            return Vector2Df(rectangle.x + rectangle.width, rectangle.y + rectangle.height / 2.0f);
        case UIOrigin::BOTTOM_LEFT:
            return Vector2Df(rectangle.x, rectangle.y + rectangle.height);
        case UIOrigin::BOTTOM:
            return Vector2Df(rectangle.x + rectangle.width / 2.0f, rectangle.y + rectangle.height);
        case UIOrigin::BOTTOM_RIGHT:
            return Vector2Df(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
    }

    return Vector2Df();
}

void UITransformComponent::_screen_resize_listener_call(int width, int height) {
    log_trace(this, __PRETTY_FUNCTION__, width, height);

    Vector2Df relative_position = this->get_position();

    this->_base_rectangle = Rectangle{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)};

    this->set_position(relative_position);
}
