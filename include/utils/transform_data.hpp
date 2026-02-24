#pragma once

#include "vector.hpp"

namespace utils {

struct TransformData {
    TransformData() : position(Vector2Df()), rotation(0), scale(Vector2Df(1.0f)) {}

    TransformData(Vector2Df position, float rotation, Vector2Df scale)
        : position(position),
          rotation(rotation),
          scale(scale) {}

    Vector2Df position;
    float rotation;
    Vector2Df scale;
};

inline std::ostream &operator<<(std::ostream &ostream, const TransformData &transform_data) {
    ostream << "TransformData {" << transform_data.position << ", " << transform_data.rotation << ", "
            << transform_data.scale << "}";

    return ostream;
}

}  // namespace utils
