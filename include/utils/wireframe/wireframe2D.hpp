#pragma once

#include "types.hpp"
namespace utils {

enum class Wireframe2DType { POINT, LINE, RECTANGLE, CIRCLE };

template <Numeric T>
class Wireframe2D {
   public:
    Wireframe2D(Wireframe2DType type) : _type(type) {}

    ~Wireframe2D() = default;

    virtual inline Vector2D<T> position() = 0;

    virtual inline float rotation() = 0;

    inline Wireframe2DType wireframe2DType() const { return this->_type; }

   private:
    Wireframe2DType _type;
};

}  // namespace utils
