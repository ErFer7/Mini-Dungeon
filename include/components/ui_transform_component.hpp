#pragma once

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "component.hpp"
#include "components/transform_component.hpp"
#include "graphics_component.hpp"
#include "raylib.h"

enum class UIOrigin { TOP_LEFT, TOP, TOP_RIGHT, LEFT, CENTER, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT };

// TODO: Rethink the name for this component, it is more like an adapter than a component actually
class UITransformComponent : public Component {
   public:
    UITransformComponent(GameCore *game_core, Entity *entity, UIOrigin ui_origin, UITransformComponent *parent_ui_transform = nullptr);

    // TODO: Handle the destruction of the parent
    ~UITransformComponent() override { this->unregister_component(); };

    Vector2 get_position() const;

    // TODO: Handle case where the parent is null
    inline float get_rotation() const {
        return this->_transform_component->get_relative_rotation(this->_parent_transform_component->get_rotation());
    }

    inline Vector2 get_scale() const {
        return this->_transform_component->get_relative_scale(this->_parent_transform_component->get_scale());
    }

    void set_position(Vector2 position);

    void set_rotation(float rotation);

    void set_scale(Vector2 scale);

   protected:
    void register_component() override {};

    void unregister_component() override {};

   private:
    Vector2 _get_origin() const;

    Vector2 _get_anchor_point() const;  // The point in the UI entity that is considered to be the "center" or the origin

    Vector2 _rect_point_by_ui_origin(Rectangle rectangle) const;

    Vector2 _position_to_ui_position(Vector2 position) const;

    Vector2 _ui_position_to_position(Vector2 ui_position) const;

   private:
    UIOrigin _ui_origin;
    UITransformComponent *_parent_ui_transform;
    TransformComponent *_parent_transform_component;
    GraphicsComponent *_parent_graphics_component;
    TransformComponent *_transform_component;
    GraphicsComponent *_graphics_component;
};