#pragma once

#include <utility>

#include "types.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class QuadObject {
    friend class Quadtree<T>;

   public:
    QuadObject() = default;

    QuadObject(QuadObject &&other) noexcept { this->_move(std::move(other)); }

    ~QuadObject() = default;

    inline QuadObject &operator=(QuadObject &&other) noexcept {
        this->_move(std::move(other));

        return *this;
    }

   protected:
    virtual inline Vector2D<T> position() = 0;

    virtual inline float rotation() = 0;

    virtual inline Wireframe2D *wireframe2D() = 0;

   private:
    void _move(QuadObject &&other) {
        if (this == &other) {
            return;
        }
    }
};

}  // namespace utils
