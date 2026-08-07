#pragma once

#include <utility>

#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

class QuadObject {
    friend class Quadtree;

   public:
    QuadObject() = default;

    QuadObject(QuadObject &&other) noexcept { this->_move(std::move(other)); }

    ~QuadObject() = default;

    inline QuadObject &operator=(QuadObject &&other) noexcept {
        this->_move(std::move(other));

        return *this;
    }

   protected:
    virtual inline Wireframe2D *wireframe2D() = 0;

   private:
    void _move(QuadObject &&other) {
        if (this == &other) {
            return;
        }
    }
};

}  // namespace utils
