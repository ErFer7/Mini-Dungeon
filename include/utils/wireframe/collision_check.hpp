#pragma once

#include "utils/wireframe/line.hpp"
#include "utils/wireframe/point.hpp"
#include "utils/wireframe/wireframe2D.hpp"
namespace utils {

enum CheckResult { OUTSIDE, CLIPPING, INSIDE };

// TODO: Finish this

template <Numeric T>
CheckResult check_collision_point_to_point(const Point<T> &point_a, const Point<T> &point_b) {
    return approximately_equal<T>(point_a.position(), point_b.position()) ? INSIDE : OUTSIDE;
}

// template <Numeric T>
// CheckResult check_collision_point_line(const Point<T> &point, const Line<T> &line) {
//     // cross = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x)
//
//     Vector2D<T> point_position = point.position();
//     Vector2D<T> line_start = line.start();
//     Vector2D<T> line_end = line.end();
//
//     if constexpr (std::same_as<T, int>) {
//     }
// }

template <Numeric T>
inline CheckResult check_collision(const Wireframe2D &wireframe_a, const Wireframe2D &wireframe_b) {
    switch (wireframe_a.wireframe2DType()) {
        case Wireframe2DType::POINT: {
            switch (wireframe_b.wireframe2DType()) {
                case utils::Wireframe2DType::POINT:
                    return check_collision_point_to_point<T>(wireframe_a, wireframe_b);
                default:
                    break;
            }

            break;
        }
        default:
            break;
    }

    return OUTSIDE;
}

}  // namespace utils
