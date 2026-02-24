#include "managers/graphics/space.hpp"

#include "components/graphics_component.hpp"

void Space::add_component(Handle<GraphicsComponent> component) { this->_components->push_back(component); }

void Space::remove_component(Handle<GraphicsComponent> component) {
    this->_components->erase(std::remove(this->_components->begin(), this->_components->end(), component),
                             this->_components->end());
}

void Space::sort() {
    switch (this->_sorting_mode) {
        case SortingMode::NONE:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](Handle<GraphicsComponent> comp_a, Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        case SortingMode::TOP_TO_DOWN:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](Handle<GraphicsComponent> comp_a, Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          if (comp_a->get_layer() == comp_b->get_layer()) {
                              return comp_a->_get_position().y > comp_b->_get_position().y;
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        case SortingMode::ISOMETRIC:
            std::sort(this->_components->begin(),
                      this->_components->end(),
                      [](Handle<GraphicsComponent> comp_a, Handle<GraphicsComponent> comp_b) -> bool {
                          if (comp_a.is_null()) {
                              return true;
                          } else if (comp_b.is_null()) {
                              return false;
                          }

                          if (comp_a->get_layer() == comp_b->get_layer()) {
                              return (comp_a->_get_position().x + comp_a->_get_position().y) <
                                     (comp_b->_get_position().x + comp_b->_get_position().y);
                          }

                          return comp_a->get_layer() < comp_b->get_layer();
                      });
            break;
        default:
            break;
    }
}

void Space::draw() {
    for (auto component : *this->_components) {
        if (component->is_active()) {
            component->draw();
        }
    }
}
