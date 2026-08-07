#pragma once

#include <vector>

#include "utils/id/handle.hpp"
#include "utils/id/id_references.hpp"
#include "utils/vector.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric NumType, QuadObject ObjType>
class Quadtree {
   private:
    struct Quad {
        Vector2D<NumType> position;  // Center
        NumType size;
        std::unique_ptr<Quad> children[4];
        std::vector<Handle<ObjType>> objects;

        Quad(Vector2D<NumType> position, NumType size) : position(position), size(size) {}

        bool insert(const Handle<ObjType> &object, const Vector2D<NumType> &position) {
            // Check
            // Fits: subdivide
            // Clips: subdivide
            // Outside: nothing
        }
    };

   public:
    Quadtree(NumType initial_base_size) : _root(std::make_unique<Quad>(Vector2D<NumType>(), initial_base_size)) {}

    void insert(const Handle<ObjType> &object, const Vector2D<NumType> &position) {}

   private:
    std::unique_ptr<Quad> _root;
};

}  // namespace utils
