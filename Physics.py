# -*- coding: utf-8 -*-

import pygame
import core

def update_physics(rooms, room_index, render_control, game_state, monster_ammount):

    entities = rooms[room_index[0]][room_index[1]].entities
    dead_entities_keys = []

    for key in entities:

        if key != "Player" and not key.endswith("drop"):

            entities[key].update(entities["Player"].position, rooms[room_index[0]][room_index[1]].collision_sprites.sprites())

        if entities[key].is_attacking() or key.endswith("drop"):

            for sub_key in entities:

                if sub_key != key and not (key.startswith("Monster") and sub_key.startswith("Monster")):

                    if not key.endswith("drop"):

                        successful_attack = False

                        if key.startswith("Monster"):

                            successful_attack = pygame.sprite.collide_rect(entities[key].sprites.sprites()[0], entities[sub_key].sprites.sprites()[0])
                        else:

                            successful_attack = pygame.sprite.collide_rect(entities[key].sprites.sprites()[0].item_sprite, entities[sub_key].sprites.sprites()[0])

                        if successful_attack:

                            entities[sub_key].change_life(-entities[key].power)

                            if entities[sub_key].position[0] >= entities[key].position[0]:

                                entities[sub_key].velocity[0] += 3.0
                            else:

                                entities[sub_key].velocity[0] -= 3.0

                            if entities[sub_key].is_dead():

                                if sub_key != "Player":

                                    entities["Player"].kill_count += 1

                                    if entities["Player"].kill_count == monster_ammount:

                                        game_state.state = core.State.WON
                                        game_state.level += 1

                                        if game_state.level == 25:

                                            game_state.state = core.State.FINISHED

                                    dead_entities_keys.append(sub_key)
                                    render_control.update_all = True
                                else:

                                    game_state.state = core.State.LOST
                    else:

                        if sub_key == "Player" and pygame.sprite.collide_rect(entities[key].sprites.sprites()[0], entities[sub_key].sprites.sprites()[0]):

                            entities[sub_key].change_life(20)
                            dead_entities_keys.append(key)

        colliders = pygame.sprite.spritecollide(entities[key].sprites.sprites()[0], rooms[room_index[0]][room_index[1]].collision_sprites, False)
        trigger = pygame.sprite.spritecollideany(entities[key].sprites.sprites()[0], rooms[room_index[0]][room_index[1]].trigger_sprites)
        
        for collider in colliders:

            if collider is not None:
                
                entities[key].position[0] -= entities[key].velocity[0] * (1 + entities[key].drag)
                entities[key].position[1] -= entities[key].velocity[1] * (1 + entities[key].drag)
                entities[key].velocity[0] = 0.0
                entities[key].velocity[1] = 0.0

        if key.startswith("Monster"):

            if trigger is not None:
                    
                entities[key].position[0] -= entities[key].velocity[0] * (1 + entities[key].drag)
                entities[key].position[1] -= entities[key].velocity[1] * (1 + entities[key].drag)
                entities[key].velocity[0] = 0.0
                entities[key].velocity[1] = 0.0

        if entities[key].direction[0] == 0:

            if abs(entities[key].velocity[0]) >= 0.01:

                entities[key].velocity[0] /= 1 + entities[key].drag
            else:

                entities[key].velocity[0] = 0.0
            
        if entities[key].direction[1] == 0:

            if abs(entities[key].velocity[1]) >= 0.01:

                entities[key].velocity[1] /= 1 + entities[key].drag
            else:

                entities[key].velocity[1] = 0.0
            
        entities[key].position[0] += entities[key].velocity[0]
        entities[key].position[1] += entities[key].velocity[1]

        if trigger is not None and key == "Player":

            if trigger.direction == 0:

                temp = room_index[0]
                room_index[0] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][1] - 10
            elif trigger.direction == 1:

                temp = room_index[0]
                room_index[0] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][1] + 10
            elif trigger.direction == 2:

                temp = room_index[1]
                room_index[1] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][0] + 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][1]
            else:

                temp = room_index[1]
                room_index[1] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][0] - 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][1]
            
            rooms[room_index[0]][room_index[1]].entities[key].sprites.update((rooms[room_index[0]][room_index[1]].entities[key].position[0] - 16, rooms[room_index[0]][room_index[1]].entities[key].position[1] - 16), rooms[room_index[0]][room_index[1]].entities[key].direction[0], rooms[room_index[0]][room_index[1]].entities[key].is_attacking())
            render_control.update_all = True
            break
        
        if not key.endswith("drop"):

            rooms[room_index[0]][room_index[1]].entities[key].sprites.update((rooms[room_index[0]][room_index[1]].entities[key].position[0] - 16, rooms[room_index[0]][room_index[1]].entities[key].position[1] - 16), rooms[room_index[0]][room_index[1]].entities[key].direction[0], rooms[room_index[0]][room_index[1]].entities[key].is_attacking())

    for key in dead_entities_keys:

        if not key.endswith("drop"):

            rooms[room_index[0]][room_index[1]].entities[key].drop(rooms[room_index[0]][room_index[1]].entities, key)
        
        rooms[room_index[0]][room_index[1]].entities[key].delete()
        del rooms[room_index[0]][room_index[1]].entities[key]