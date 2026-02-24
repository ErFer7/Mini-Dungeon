#include "utils/transform.hpp"

#include "utils/transform_data.hpp"

using utils::TransformData;

const TransformData utils::Transform::get_relative_transform_data(TransformData origin) const {
    TransformData result = this->_transform_data;
    result.position = this->get_relative_position(origin.position);
    result.rotation = this->get_relative_rotation(origin.rotation);
    result.scale = this->get_relative_scale(origin.scale);

    return result;
}

void utils::Transform::set_relative_transform_data(TransformData origin, TransformData offset) {
    this->set_relative_position(offset.position, origin.position);
    this->set_relative_rotation(origin.position, origin.rotation, offset.rotation);
    this->set_relative_scale(offset.scale, origin.scale, offset.scale);
}

void utils::Transform::rotate(Vector2Df origin, float rotation) {
    this->_transform_data.position = this->_transform_data.position - origin;
    this->_transform_data.position.rotate(DEG2RAD * rotation);
    this->_transform_data.rotation = this->_transform_data.rotation + rotation;
    this->_transform_data.position = this->_transform_data.position + origin;
}

void utils::Transform::scale(Vector2Df origin, Vector2Df scale) {
    this->_transform_data.position = this->_transform_data.position - origin;
    this->_transform_data.position.rotate(DEG2RAD * -this->_transform_data.rotation);
    this->_transform_data.position = this->_transform_data.position * scale;
    this->_transform_data.scale = this->_transform_data.scale * scale;
    this->_transform_data.position.rotate(DEG2RAD * this->_transform_data.rotation);
    this->_transform_data.position = this->_transform_data.position + origin;
}
