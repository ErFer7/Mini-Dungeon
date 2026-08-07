#pragma once

#include <type_traits>
#include "utils/wireframe/line.hpp"
#include "utils/wireframe/point.hpp"
#include "utils/wireframe/wireframe2D.hpp"
namespace utils {

enum CheckResult { OUTSIDE, CLIPPING, INSIDE };

// TODO: Finish this
template <Numeric T>
CheckResult check_collision_point_line(const Point<T> &point, const Line<T> &line) {
    // cross = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x)

    Vector2D<T> point_position = point.position();
    Vector2D<T> line_start = line.start();
    Vector2D<T> line_end = line.end();

    if constexpr (std::same_as<T, int>) {

    }
}

inline CheckResult check_collision(const Wireframe2D &wireframe_a, const Wireframe2D &wireframe_b) {}

}  // namespace utils
