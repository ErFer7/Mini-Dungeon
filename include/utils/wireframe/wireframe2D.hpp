#pragma once

namespace utils {

enum class Wireframe2DType { POINT, LINE, RECTANGLE, CIRCLE };

class Wireframe2D {
   public:
    Wireframe2D(Wireframe2DType type) : _type(type) {}

    ~Wireframe2D() = default;

    inline Wireframe2DType wireframe2DType() const { return this->_type; }

   private:
    Wireframe2DType _type;
};

}  // namespace utils
