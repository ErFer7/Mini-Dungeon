#pragma once

#include "raymath.h"

struct Transform2D {
    Transform2D() : position(Vector2Zero()), rotation(0), scale(Vector2One()) {}
    Transform2D(Vector2 position, float rotation, Vector2 scale) : position(position), rotation(rotation), scale(scale) {}

    Vector2 position;
    float rotation;
    Vector2 scale;
};

struct Transform3D {
    Transform3D() : position(Vector3Zero()), rotation(Vector3Zero()), scale(Vector3One()) {}
    Transform3D(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale) {}

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};
