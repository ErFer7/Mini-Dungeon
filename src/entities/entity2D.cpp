#include "../../include/entities/entity2D.hpp"

#include "../../include/components/graphics2D_component.hpp"
#include "../../include/components/transform2D_component.hpp"

Entity2D::Entity2D(EngineCore *engine_core, Entity *parent) : Entity(engine_core, parent) {
    this->_transform_component = this->create_component<Transform2DComponent>();
    this->_graphics_component = this->create_component<Graphics2DComponent>();
}