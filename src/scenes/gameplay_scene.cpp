#include "scenes/gameplay_scene.hpp"

#include "entities/physical_entity2D.hpp"
#include "game_core.hpp"
#include "managers/graphics_component_manager.hpp"
#include "raylib.h"

void GameplayScene::init() {
    Texture2D player_texture = LoadTexture("assets/sprites/characters/Char_0.png");

    this->_player = this->get_game_core()->get_entity_container()->create_entity<Player>(
        PhysicalEntity2DArgs{.texture = player_texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D});

    this->_player->set_active(false);
}

void GameplayScene::enter() { this->_player->set_active(true); }
