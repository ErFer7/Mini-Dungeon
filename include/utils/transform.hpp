#pragma once

#include <raylib.h>

#include "raymath.h"
#include "transform_data.hpp"

namespace utils {

class Transform {
   public:
    Transform(){};

    ~Transform() = default;

    inline const TransformData get_transform_data() const { return this->_transform_data; }

    inline const Vector2 get_position() const { return this->_transform_data.position; }

    inline float get_rotation() const { return this->_transform_data.rotation; }

    inline const Vector2 get_scale() const { return this->_transform_data.scale; }

    const TransformData get_relative_transform_data(TransformData origin) const;

    inline const Vector2 get_relative_position(Vector2 origin_position) const {
        return Vector2Subtract(this->_transform_data.position, origin_position);
    }

    inline float get_relative_rotation(float origin_rotation) const { return this->_transform_data.rotation - origin_rotation; }

    inline const Vector2 get_relative_scale(Vector2 origin_scale) const { return Vector2Divide(this->_transform_data.scale, origin_scale); }

    inline void set_transform_data(TransformData result) { this->_transform_data = result; }

    void set_relative_transform_data(TransformData origin, TransformData offset);

    inline void set_position(Vector2 position) { this->_transform_data.position = position; }

    inline void set_rotation(float rotation) { this->_transform_data.rotation = rotation; }

    inline void set_scale(Vector2 scale) { this->_transform_data.scale = scale; }

    inline void set_relative_position(Vector2 origin_position, Vector2 offset_position) {
        this->_transform_data.position = Vector2Add(origin_position, offset_position);
    }

    void set_relative_rotation(Vector2 origin, float origin_rotation, float offset_rotation) {
        float diff_rotation = offset_rotation - (this->_transform_data.rotation - origin_rotation);
        this->rotate(origin, diff_rotation);
    }

    void set_relative_scale(Vector2 origin, Vector2 origin_scale, Vector2 offset_scale) {
        Vector2 diff_scale = Vector2Divide(offset_scale, Vector2Divide(this->_transform_data.scale, origin_scale));
        this->scale(origin, diff_scale);
    }

    inline void translate(Vector2 translation) { this->_transform_data.position = Vector2Add(this->_transform_data.position, translation); }

    void rotate(Vector2 origin, float rotation) {
        this->_transform_data.position = Vector2Subtract(this->_transform_data.position, origin);
        this->_transform_data.position = Vector2Rotate(this->_transform_data.position, DEG2RAD * rotation);
        this->_transform_data.rotation = this->_transform_data.rotation + rotation;
        this->_transform_data.position = Vector2Add(this->_transform_data.position, origin);
    }

    void scale(Vector2 origin, Vector2 scale) {
        this->_transform_data.position = Vector2Subtract(this->_transform_data.position, origin);
        this->_transform_data.position = Vector2Rotate(this->_transform_data.position, DEG2RAD * -this->_transform_data.rotation);
        this->_transform_data.position = Vector2Multiply(this->_transform_data.position, scale);
        this->_transform_data.scale = Vector2Multiply(this->_transform_data.scale, scale);
        this->_transform_data.position = Vector2Rotate(this->_transform_data.position, DEG2RAD * this->_transform_data.rotation);
        this->_transform_data.position = Vector2Add(this->_transform_data.position, origin);
    }

   private:
    TransformData _transform_data;
};

}  // namespace game
