#pragma once

#include "types.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class Rectangle : Wireframe2D {
    Rectangle() = default;

    Rectangle(T x, T y, T width, T height)
        : Wireframe2D(Wireframe2DType::RECTANGLE),
          _position(Vector2D<T>(x, y)),
          _width(width),
          _height(height) {}

    Rectangle(Vector2D<T> position, T size)
        : Wireframe2D(Wireframe2DType::RECTANGLE),
          _position(position),
          _width(size),
          _height(size) {}

    Rectangle(Vector2D<T> position, T width, T height)
        : Wireframe2D(Wireframe2DType::RECTANGLE),
        _position(position),
        _width(width),
        _height(height) {}

    ~Rectangle() = default;

   private:
    Vector2D<T> _position;
    T _width;
    T _height;
};

}  // namespace utils
