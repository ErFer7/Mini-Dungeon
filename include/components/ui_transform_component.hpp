#pragma once

#include <raylib.h>

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/transform_component.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

enum class UIOrigin { TOP_LEFT, TOP, TOP_RIGHT, LEFT, CENTER, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT };

struct UITransformComponentArgs {
    UIOrigin ui_origin;
    Handle<UITransformComponent> parent_ui_transform = Handle<UITransformComponent>();
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
};

// TODO: Rethink the name for this component, it is more like an adapter than a component actually
class UITransformComponent final : public Component {
   public:
    UITransformComponent(Handle<Entity> entity, const UITransformComponentArgs &args);

    UITransformComponent(UITransformComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    // TODO: Handle the destruction of the parent
    ~UITransformComponent() override = default;

    UITransformComponent &operator=(UITransformComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    Vector2Df get_position() const;

    // TODO: Handle case where the parent is null
    inline float get_rotation() const {
        return this->_transform_component->get_relative_rotation(this->_parent_transform_component->get_rotation());
    }

    inline Vector2Df get_scale() const {
        return this->_transform_component->get_relative_scale(this->_parent_transform_component->get_scale());
    }

    void set_position(Vector2Df position);

    void set_rotation(float rotation);

    void set_scale(Vector2Df scale);

    void translate(Vector2Df translation);

    void rotate(float rotation);

    void scale(Vector2Df scale);

    void debug_draw() override {}

   private:
    void _move(UITransformComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_ui_origin = std::move(other._ui_origin);
        this->_parent_ui_transform = std::move(other._parent_ui_transform);
        this->_parent_transform_component = std::move(other._parent_transform_component);
        this->_parent_graphics_component = std::move(other._parent_graphics_component);
        this->_transform_component = std::move(other._transform_component);
        this->_graphics_component = std::move(other._graphics_component);
    }

    Vector2Df _get_origin() const;

    // The point in the UI entity that is considered to be the "center" or the origin
    Vector2Df _get_anchor_point() const;

    Vector2Df _rect_point_by_ui_origin(Rectangle rectangle) const;

   private:
    UIOrigin _ui_origin;
    Handle<UITransformComponent> _parent_ui_transform;
    Handle<TransformComponent> _parent_transform_component;
    Handle<GraphicsComponent> _parent_graphics_component;
    Handle<TransformComponent> _transform_component;
    Handle<GraphicsComponent> _graphics_component;
};
