#pragma once

#include "types.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class Line : Wireframe2D {
    Line() = default;

    Line(T x0, T y0, T x1, T y1)
        : Wireframe2D(Wireframe2DType::LINE),
          _start(Vector2D<T>(x0, y0)),
          _end(Vector2D<T>(x1, y1)) {}

    Line(Vector2D<T> start, Vector2D<T> end) : Wireframe2D(Wireframe2DType::LINE), _start(start), _end(end) {}

    ~Line() = default;

    inline Vector2D<T> start() const { return this->_start; }

    inline Vector2D<T> end() const { return this->_end; }

   private:
    Vector2D<T> _start;
    Vector2D<T> _end;
};

}  // namespace utils
