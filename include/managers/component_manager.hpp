#pragma once

#include <memory>
#include <vector>

#include "../components/component.hpp"
#include "../types.hpp"
#include "manager.hpp"

class ComponentManager : public Manager {
   public:
    typedef std::vector<Component *> ComponentVector;

    ComponentManager(const ComponentManager &other) noexcept = delete;

    ComponentManager(ComponentManager &&other) noexcept = delete;

    ComponentManager(EngineCore *engine_core) : Manager(engine_core) { this->_components = std::make_unique<ComponentVector>(); }

    ~ComponentManager() override = default;

    ComponentManager &operator=(const ComponentManager &other) noexcept = delete;

   protected:
    ComponentVector *get_components() { return this->_components.get(); }

    virtual inline void register_component(Component *component) { this->_components->push_back(component); }

    virtual void unregister_component(Component *component) {
        this->_components->erase(std::remove(this->_components->begin(), this->_components->end(), component), this->_components->end());
    }

   private:
    std::unique_ptr<ComponentVector> _components;
};
