#pragma once

#include "types.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class Circle : Wireframe2D {
    Circle() = default;

    Circle(T x, T y, T radius) : Wireframe2D(Wireframe2DType::CIRCLE), _position(Vector2D<T>(x, y)), _radius(radius) {}

    Circle(Vector2D<T> position, T radius)
        : Wireframe2D(Wireframe2DType::CIRCLE),
          _position(position),
          _radius(radius) {}

    ~Circle() = default;

   private:
    Vector2D<T> _position;
    T _radius;
};

}  // namespace utils
