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
    GraphicsComponent(Entity *entity, const GraphicsComponentArgs &args);

    GraphicsComponent(GraphicsComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~GraphicsComponent() override = default;

    GraphicsComponent &operator=(GraphicsComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

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

    void _move(GraphicsComponent &&other) {
        // TODO: Maybe use std::move for everything? Would this avoid unecessary copies?
        if (this != &other) {
            this->_texture = std::move(other._texture);
            this->_transform_component = std::move(other._transform_component);
            this->_source_rectangle = std::move(other._source_rectangle);
            this->_destination_rectangle = std::move(other._destination_rectangle);
            this->_origin = std::move(other._origin);
            this->_rotation = other._rotation;
            this->_texture_scale = other._texture_scale;
            this->_color = std::move(other._color);
            this->_rendering_mode = std::move(other._rendering_mode);
            this->_layer = other._layer;
            this->_transform_update_listener = std::move(other._transform_update_listener);
            this->_on_destroy_listener = std::move(other._on_destroy_listener);
        }
    }

    // TODO: Check the way that methods are divided
    void _update_drawing_transform();

    void _update_drawing_transform_listener_call(const Vector2Df &, const TransformData &) {
        this->_update_drawing_transform();
    }

    void _unregister_on_space();

    void _unregister_on_space_listener_call(utils::Handle<Component>) { this->_unregister_on_space(); }

   private:
    Texture2D _texture;
    utils::Handle<TransformComponent> _transform_component;
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
