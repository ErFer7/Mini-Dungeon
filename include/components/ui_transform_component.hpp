#pragma once

#include <raylib.h>

#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "components/transform_component.hpp"
#include "entities/entity.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

enum class UIOrigin { TOP_LEFT, TOP, TOP_RIGHT, LEFT, CENTER, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT };

struct UITransformComponentArgs {
    UIOrigin ui_origin;
    UITransformComponent *parent_ui_transform = nullptr;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
};

// TODO: Rethink the name for this component, it is more like an adapter than a component actually
class UITransformComponent final : public Component {
   public:
    UITransformComponent(Entity *entity, const UITransformComponentArgs &args);

    UITransformComponent(UITransformComponent &&other) = default;

    // TODO: Handle the destruction of the parent
    ~UITransformComponent() override = default;

    UITransformComponent &operator=(UITransformComponent &&other) noexcept = default;

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

   private:
    Vector2Df _get_origin() const;

    // The point in the UI entity that is considered to be the "center" or the origin
    Vector2Df _get_anchor_point() const;

    Vector2Df _rect_point_by_ui_origin(Rectangle rectangle) const;

   private:
    UIOrigin _ui_origin;
    UITransformComponent *_parent_ui_transform;
    TransformComponent *_parent_transform_component;
    GraphicsComponent *_parent_graphics_component;
    TransformComponent *_transform_component;
    GraphicsComponent *_graphics_component;
};
