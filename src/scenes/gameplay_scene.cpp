#include "scenes/gameplay_scene.hpp"

#include "containers/entity_container.hpp"
#include "entities/dynamic_physical_entity2D.hpp"
#include "entities/gameplay/player.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "game_core.hpp"
#include "gameplay/dungeon.hpp"
#include "managers/graphics_component_manager.hpp"
#include "raylib.h"
#include "types.hpp"
#include "utils/vector.hpp"

using utils::Vector2Df;

void GameplayScene::init() {
    Texture2D player_texture =
        GameCore::get_instance()->get_texture_container()->load_texture("assets/sprites/characters/Char_0.png");

    EntityContainer *entity_container = GameCore::get_instance()->get_entity_container();

    this->_player = entity_container->create_entity<Player>(
        DynamicPhysicalEntity2DArgs{.texture = player_texture, .rendering_mode = RenderingMode::WORLD_SPACE_2D});

    this->_player->set_active(false);

    this->_was_initialized = true;
}

void GameplayScene::enter() {
    this->_player->set_active(true);
    this->_dungeon.generate();
}
