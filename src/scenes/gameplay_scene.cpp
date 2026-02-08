#include "scenes/gameplay_scene.hpp"

#include "containers/entity_container.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "game_core.hpp"
#include "managers/graphics_component_manager.hpp"
#include "raylib.h"
#include "utils/vector.hpp"

using utils::Vector2Df;

void GameplayScene::init() {
    Texture2D player_texture = LoadTexture("assets/sprites/characters/Char_0.png");
    Texture2D wall_texture = LoadTexture("assets/sprites/walls/Wall_0.png");

    EntityContainer *entity_container = GameCore::get_instance()->get_entity_container();

    this->_player = entity_container->create_entity<Player>(
        DynamicPhysicalEntity2DArgs{.texture = player_texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D});

    this->_wall = entity_container->create_entity<Wall>(StaticPhysicalEntity2DArgs{
        .texture = wall_texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D, .position = Vector2Df(64.0f, 0.0f)});

    this->_player->set_active(false);
    this->_wall->set_active(false);
}

void GameplayScene::enter() {
    this->_player->set_active(true);
    this->_wall->set_active(true);
}
