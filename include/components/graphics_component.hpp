#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "managers/graphics_component_manager.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

using utils::Vector2Df;

struct GraphicsComponentArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Color color = WHITE;
    int layer = 0;
    float texture_scale = 1.0f;
};

// TODO: Add a dirty and clean state system
class GraphicsComponent final : public Component {
    friend class Space;
    friend class GraphicsComponentManager;

   public:
    GraphicsComponent(GameCore *game_core, Entity *entity, const GraphicsComponentArgs &args);

    ~GraphicsComponent() override = default;

    inline Texture2D get_texture() const { return this->_texture; }

    void set_texture(Texture2D texture);

    inline Color get_color() const { return this->_color; }

    inline void set_color(Color color) { this->_color = color; }

    inline RenderingMode get_rendering_mode() const { return this->_rendering_mode; }

    inline int get_layer() { return this->_layer; }

    inline void set_layer(int layer) { this->_layer = layer; }

    Rectangle get_rectangle() const;

    void draw();

   private:
    inline Vector2Df _get_position() { return this->_transform_component->get_position(); }

    // TODO: Check the way that methods are divided
    void _update_drawing_transform();

    void _unregister_on_space();

   private:
    Texture2D _texture;
    TransformComponent *_transform_component;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Vector2Df _origin;
    float _rotation;
    float _texture_scale;
    Color _color;
    RenderingMode _rendering_mode;
    int _layer;
    TransformComponent::TransformUpdateListener _transform_update_listener;
    OnDestroyListener _on_destroy_listener;
};
