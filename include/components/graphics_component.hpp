#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "managers/graphics/graphics_enums.hpp"
#include "managers/graphics/graphics_manager.hpp"
#include "managers/graphics/space.hpp"
#include "raylib.h"
#include "utils/activity_state.hpp"
#include "utils/id/handle.hpp"
#include "utils/vector.hpp"

using utils::Handle;
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
    friend class GraphicsManager;

   private:
    typedef ActivityState::ActivityUpdateListener ActivityUpdateListener;

   public:
    GraphicsComponent(Handle<Entity> entity, const GraphicsComponentArgs &args);

    GraphicsComponent(GraphicsComponent &&other) noexcept : Component(std::move(other)) {
        this->_move(std::move(other));
    }

    ~GraphicsComponent() override = default;

    inline GraphicsComponent &operator=(GraphicsComponent &&other) noexcept {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Texture2D get_texture() const { return this->_texture; }

    void set_texture(Texture2D texture);

    inline Color get_color() const { return this->_color; }

    inline void set_color(Color color) { this->_color = color; }

    inline RenderingMode get_rendering_mode() const { return this->_rendering_mode; }

    // TODO: Remove the get and set from method names
    inline int get_layer() const { return this->_layer; }

    inline void set_layer(int layer) { this->_layer = layer; }

    inline bool is_flipped_vertically() { return this->_source_rectangle.height < 0; }

    inline bool is_flipped_horizontally() { return this->_source_rectangle.width < 0; }

    inline void flip_vertically() { this->_source_rectangle.height *= -1; }

    inline void flip_horizontally() { this->_source_rectangle.width *= -1; }

    inline Vector2Df get_offset() { return this->_offset; }

    inline void set_offset(const Vector2Df &offset) {
        this->_offset = offset;
        this->_update_drawing_transform();
    }

    Rectangle get_rectangle() const;

    Vector2Df get_size() const;

    void draw();

    void debug_draw() override {}

   private:
    void _move(GraphicsComponent &&other);

    // TODO: Replace with _get_transform()
    inline Vector2Df _get_position() const {
        return Vector2Df(this->_destination_rectangle.x, this->_destination_rectangle.y);
    }

    // TODO: Check the way that methods are divided
    void _update_drawing_transform();

    void _update_drawing_transform_listener_call(const Vector2Df &, const TransformData &) {
        this->_update_drawing_transform();
    }

    void _unregister_on_space();

    void _unregister_on_space_listener_call(Handle<Component>) { this->_unregister_on_space(); }

    void _handle_activity_update(Handle<Component> component);

   private:
    Texture2D _texture;
    Rectangle _source_rectangle;
    Rectangle _destination_rectangle;
    Vector2Df _origin;
    Vector2Df _offset;
    float _rotation;
    float _texture_scale;
    Color _color;
    RenderingMode _rendering_mode;
    int _layer;
    TransformComponent::TransformUpdateListener _transform_update_listener;
    OnDestroyListener _on_destroy_listener;
    ActivityUpdateListener _on_activity_update_listener;
};
