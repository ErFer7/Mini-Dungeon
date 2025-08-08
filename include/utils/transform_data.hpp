#pragma once

#include "raymath.h"

namespace utils {

struct TransformData {
    TransformData() : position(Vector2Zero()), rotation(0), scale(Vector2One()) {}
    TransformData(Vector2 position, float rotation, Vector2 scale) : position(position), rotation(rotation), scale(scale) {}

    Vector2 position;
    float rotation;
    Vector2 scale;
};

}  // namespace game
