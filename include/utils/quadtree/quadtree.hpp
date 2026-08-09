#pragma once

#include <vector>

#include "components/collider_component.hpp"
#include "utils/id/handle.hpp"
#include "utils/id/id_references.hpp"
#include "utils/vector.hpp"
#include "utils/wireframe/rectangle.hpp"
#include "utils/wireframe/wireframe2D.hpp"

namespace utils {

template <Numeric T>
class Quadtree {
   private:
    typedef std::vector<Handle<QuadObject<T>>> QuadObjects;

    struct Quad {
        utils::Rectangle<T> rectangle;
        std::unique_ptr<Quad> children[4];
        QuadObjects contained_objects;
        QuadObjects clipping_objects;

        Quad(Vector2D<T> position, T size) : rectangle(Rectangle<T>(position, size)) {}

        bool insert(const Handle<T> &object, const Vector2D<T> &position) {
            // Check

            check_collision<T>()

            // Fits: subdivide
            // Clips: subdivide
            // Outside: nothing
        }
    };

   public:
    Quadtree(T initial_base_size) : _root(std::make_unique<Quad>(Vector2D<T>(), initial_base_size)) {}

    void insert(const Handle<T> &object, const Vector2D<T> &position) {}

   private:
    std::unique_ptr<Quad> _root;
};

}  // namespace utils
