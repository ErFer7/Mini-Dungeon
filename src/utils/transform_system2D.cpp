#include "../../include/utils/transform_system2D.hpp"

const Transform2D TransformSystem2D::get_relative(Transform2D origin) const {
    Transform2D result = this->_absolute;
    result.position = Vector2Subtract(this->_absolute.position, origin.position);
    result.rotation = this->_absolute.rotation - origin.rotation;
    result.scale = Vector2Divide(this->_absolute.scale, origin.scale);

    return result;
}

void TransformSystem2D::set_relative(Transform2D origin, Transform2D offset) {
    this->set_relative_position(offset.position, origin.position);
    this->set_relative_rotation(origin.position, origin.rotation, offset.rotation);
    this->set_relative_scale(offset.scale, origin.scale, offset.scale);
}
