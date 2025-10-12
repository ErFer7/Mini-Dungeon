#pragma once

#include "vector.hpp"

namespace utils {

struct TransformData {
    TransformData() : position(Vector2Df()), rotation(0), scale(Vector2Df(1.0f)) {}
    TransformData(Vector2Df position, float rotation, Vector2Df scale) : position(position), rotation(rotation), scale(scale) {}

    Vector2Df position;
    float rotation;
    Vector2Df scale;
};

}  // namespace utils
