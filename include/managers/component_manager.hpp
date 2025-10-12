#pragma once

#include <memory>
#include <vector>

#include "components/component.hpp"
#include "managers/manager.hpp"

using std::make_unique;
using std::remove;
using std::unique_ptr;
using std::vector;

class ComponentManager : public Manager {
   public:
    typedef vector<Component *> ComponentVector;

   public:
    ComponentManager() = default;

    ComponentManager(GameCore *game_core) : Manager(game_core) { this->_components = make_unique<ComponentVector>(); }

    ~ComponentManager() override = default;

   protected:
    ComponentVector *get_components() { return this->_components.get(); }

    virtual inline void register_component(Component *component) { this->_components->push_back(component); }

    virtual void unregister_component(Component *component) {
        this->_components->erase(remove(this->_components->begin(), this->_components->end(), component), this->_components->end());
    }

   private:
    unique_ptr<ComponentVector> _components;
};
