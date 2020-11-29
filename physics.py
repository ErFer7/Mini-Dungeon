# -*- coding: utf-8 -*-

'''
Este módulo processa a física do jogo
'''

import pygame
import core

def update_physics(rooms, room_index, render_control, game_state, monster_ammount, sound_channel):
    
    '''
    Atualiza toda a física
    '''

    entities = rooms[room_index[0]][room_index[1]].entities # Obtém as entidades
    dead_entities_keys = [] # Lista para a eliminação de entidades mortas

    for key in entities: # Para cada entidade na sala

        if key != "Player" and not key.endswith("drop"): # Se a entidade é um monstro

            # Processa o comportamento do monstro
            entities[key].update(entities["Player"].position,
                                 rooms[room_index[0]][room_index[1]].collision_sprites.sprites())

        # Caso a entidade esteja atacando ou seja uma poção
        if entities[key].is_attacking() or key.endswith("drop"):

            for sub_key in entities: # Para cada entidade

                # Evita danos a si mesmo e dano entre monstros durante o ataque
                if sub_key != key and not (key.startswith("Monster") and sub_key.startswith("Monster")):

                    if not key.endswith("drop"): # Caso não seja poção

                        successful_attack = False # Definição do ataque

                        if key != "Player": # Se a entidade é um monstro

                            # Verifica se o monstro acertou o jogador
                            successful_attack = pygame.sprite.collide_rect(entities[key].sprites.sprites()[0],
                                                                           entities["Player"].sprites.sprites()[0])
                        else:

                            # Verifica se o jogador acertou o monstro
                            successful_attack = pygame.sprite.collide_rect(entities["Player"].sprites.sprites()[0].item_sprite,
                                                                           entities[sub_key].sprites.sprites()[0])

                        if successful_attack: # Caso o ataque seja bem sucedido

                            # Modifica a vida da entidade que recebeu o ataque
                            entities[sub_key].change_life(-entities[key].power)

                            # Toca o som do ataque
                            sound_channel.stop()
                            sound_channel.play(entities[key].attack_sound)

                            # Aplica uma velocidade (Empurrão)
                            if entities[sub_key].position[0] >= entities[key].position[0]:

                                entities[sub_key].velocity[0] += 3.0
                            else:

                                entities[sub_key].velocity[0] -= 3.0

                            if entities[sub_key].is_dead(): # Caso a entidade tenha ficado com 0 de vida

                                if sub_key != "Player": # Caso a entidade seja um monstro

                                    entities["Player"].kill_count += 1

                                    # Toca o som de eliminação
                                    sound_channel.stop()
                                    sound_channel.play(entities["Player"].kill_sound)

                                    # Condição de vitória da fase
                                    if entities["Player"].kill_count == monster_ammount:

                                        game_state.state = core.State.WON
                                        game_state.level += 1

                                        if game_state.level == game_state.max_level:

                                            game_state.state = core.State.FINISHED

                                    # Coloca a entidade na lista de eliminações e define que a tela deve ser
                                    # atualizada
                                    dead_entities_keys.append(sub_key)
                                    render_control.update_all = True
                                else: # Caso o jogador tenha morrido

                                    # Toca o som de fim de jogo
                                    sound_channel.stop()
                                    sound_channel.play(entities["Player"].game_over_sound)

                                    game_state.state = core.State.LOST
                    else: # Caso seja uma poção

                        # Caso a poção esteja colidindo com o jogador
                        if pygame.sprite.collide_rect(entities[key].sprites.sprites()[0],
                                                      entities["Player"].sprites.sprites()[0]):

                            # Toca o som da poção
                            sound_channel.stop()
                            sound_channel.play(entities[key].heal_sound)
                            
                            entities[sub_key].change_life(20) # Modifica a vida do jogador
                            dead_entities_keys.append(key) # Adiciona a poção na lista de eliminações

        # Lista de sprites de colisão que colidem com a entidade
        colliders = pygame.sprite.spritecollide(entities[key].sprites.sprites()[0],
                                                rooms[room_index[0]][room_index[1]].collision_sprites,
                                                False)

        # Lista de sprites de gatilho (portas) que colidem com a entidade
        trigger = pygame.sprite.spritecollideany(entities[key].sprites.sprites()[0],
                                                 rooms[room_index[0]][room_index[1]].trigger_sprites)

        for collider in colliders: # Para cada colisão

            if collider is not None:

                # Reverte uma iteração da posição
                entities[key].position[0] -= entities[key].velocity[0] * (1 + entities[key].drag)
                entities[key].position[1] -= entities[key].velocity[1] * (1 + entities[key].drag)
                entities[key].velocity[0] = 0.0
                entities[key].velocity[1] = 0.0
                
                # Toca o som de colisão
                sound_channel.stop()
                sound_channel.play(entities[key].collision_sound)

        if key.startswith("Monster"): # Se é um monstro

            if trigger is not None:
                
                # Reverte uma iteração da posição
                entities[key].position[0] -= entities[key].velocity[0] * (1 + entities[key].drag)
                entities[key].position[1] -= entities[key].velocity[1] * (1 + entities[key].drag)
                entities[key].velocity[0] = 0.0
                entities[key].velocity[1] = 0.0

                # Toca o som de colisão
                sound_channel.stop()
                sound_channel.play(entities[key].collision_sound)

        if entities[key].direction[0] == 0: # Se não há movimentação horizontal

            if abs(entities[key].velocity[0]) >= 0.01: # Caso a velocidade ainda não esteja próxima de 0

                entities[key].velocity[0] /= 1 + entities[key].drag # Calcula a velocidade horizontal
            else:

                entities[key].velocity[0] = 0.0

        if entities[key].direction[1] == 0: # Se não há movimentação vertical

            if abs(entities[key].velocity[1]) >= 0.01: # Caso a velocidade ainda não esteja próxima de 0

                entities[key].velocity[1] /= 1 + entities[key].drag # Calcula a velocidade vertical
            else:

                entities[key].velocity[1] = 0.0

        # Calcula as novas posições
        entities[key].position[0] += entities[key].velocity[0]
        entities[key].position[1] += entities[key].velocity[1]

        if trigger is not None and key == "Player": # No caso do jogador passar por uma porta

            # Quando o jogador passa por uma porta ele é movido para o dicionário da outra sala.
            # A entidade na sala anterior é removida.

            if trigger.direction == 0: # Porta para cima

                temp = room_index[0]
                room_index[0] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][1] - 10
            elif trigger.direction == 1: # Porta para baixo

                temp = room_index[0]
                room_index[0] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][1] + 10
            elif trigger.direction == 2: # Porta para a direita

                temp = room_index[1]
                room_index[1] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][0] + 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][1]
            else: # Porta para a esquerda

                temp = room_index[1]
                room_index[1] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][0] - 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][1]

            # Atualiza o sprite do jogador
            rooms[room_index[0]][room_index[1]].entities[key].sprites.update(rooms[room_index[0]][room_index[1]].entities[key].position,
                                                                             rooms[room_index[0]][room_index[1]].entities[key].direction[0],
                                                                             rooms[room_index[0]][room_index[1]].entities[key].is_attacking())
            
            render_control.update_all = True # Define que toda a tela deve ser atualizada
            break # Quebra o loop

        if not key.endswith("drop"): # Caso seja um monstro

            # Atualiza o sprite do monstro
            rooms[room_index[0]][room_index[1]].entities[key].sprites.update(rooms[room_index[0]][room_index[1]].entities[key].position,
                                                                             rooms[room_index[0]][room_index[1]].entities[key].direction[0],
                                                                             rooms[room_index[0]][room_index[1]].entities[key].is_attacking())

    for key in dead_entities_keys: # Para cada entidade morta

        if not key.endswith("drop"): # Caso seja um monstro calcula o drop de poções

            rooms[room_index[0]][room_index[1]].entities[key].drop(rooms[room_index[0]][room_index[1]].entities, key)
        
        # Deleta a entidade
        rooms[room_index[0]][room_index[1]].entities[key].delete()
        del rooms[room_index[0]][room_index[1]].entities[key]
