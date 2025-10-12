#pragma once

#include "transform_data.hpp"

namespace utils {

class Transform {
   public:
    Transform() = default;

    Transform(Vector2Df position, float rotation, Vector2Df scale) : _transform_data(position, rotation, scale) {}

    ~Transform() = default;

    inline const TransformData get_transform_data() const { return this->_transform_data; }

    inline const Vector2Df get_position() const { return this->_transform_data.position; }

    inline float get_rotation() const { return this->_transform_data.rotation; }

    inline const Vector2Df get_scale() const { return this->_transform_data.scale; }

    const TransformData get_relative_transform_data(TransformData origin) const;

    inline const Vector2Df get_relative_position(Vector2Df origin_position) const {
        return this->_transform_data.position - origin_position;
    }

    inline float get_relative_rotation(float origin_rotation) const {
        return this->_transform_data.rotation - origin_rotation;
    }

    inline const Vector2Df get_relative_scale(Vector2Df origin_scale) const {
        return this->_transform_data.scale / origin_scale;
    }

    inline void set_transform_data(TransformData result) { this->_transform_data = result; }

    void set_relative_transform_data(TransformData origin, TransformData offset);

    inline void set_position(Vector2Df position) { this->_transform_data.position = position; }

    inline void set_rotation(float rotation) { this->_transform_data.rotation = rotation; }

    inline void set_scale(Vector2Df scale) { this->_transform_data.scale = scale; }

    inline void set_relative_position(Vector2Df origin_position, Vector2Df offset_position) {
        this->_transform_data.position = origin_position + offset_position;
    }

    void set_relative_rotation(Vector2Df origin, float origin_rotation, float offset_rotation) {
        float diff_rotation = offset_rotation - (this->_transform_data.rotation - origin_rotation);
        this->rotate(origin, diff_rotation);
    }

    void set_relative_scale(Vector2Df origin, Vector2Df origin_scale, Vector2Df offset_scale) {
        Vector2Df diff_scale = offset_scale / (this->_transform_data.scale / origin_scale);
        this->scale(origin, diff_scale);
    }

    inline void translate(Vector2Df translation) {
        this->_transform_data.position = this->_transform_data.position + translation;
    }

    void rotate(Vector2Df origin, float rotation) {
        this->_transform_data.position = this->_transform_data.position - origin;
        this->_transform_data.position.rotate(DEG2RAD * rotation);
        this->_transform_data.rotation = this->_transform_data.rotation + rotation;
        this->_transform_data.position = this->_transform_data.position + origin;
    }

    void scale(Vector2Df origin, Vector2Df scale) {
        this->_transform_data.position = this->_transform_data.position - origin;
        this->_transform_data.position.rotate(DEG2RAD * -this->_transform_data.rotation);
        this->_transform_data.position = this->_transform_data.position * scale;
        this->_transform_data.scale = this->_transform_data.scale * scale;
        this->_transform_data.position.rotate(DEG2RAD * this->_transform_data.rotation);
        this->_transform_data.position = this->_transform_data.position + origin;
    }

   private:
    TransformData _transform_data;
};

}  // namespace utils
