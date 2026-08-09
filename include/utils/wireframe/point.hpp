#pragma once

#include "types.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class Point : Wireframe2D<T> {
    Point() = default;

    Point(T x, T y) : Wireframe2D<T>(Wireframe2DType::POINT), _position(Vector2D<T>(x, y)) {}

    Point(Vector2D<T> position) : Wireframe2D<T>(Wireframe2DType::POINT), _position(position) {}

    ~Point() = default;

    inline Vector2D<T> position() override { return this->_position; }

    const inline float rotation() override { return 0.0f; }

   private:
    Vector2D<T> _position;
};

}  // namespace utils
