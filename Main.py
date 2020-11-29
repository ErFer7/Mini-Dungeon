# -*- coding: utf-8 -*-

'''
Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC
(Feito individualmente).

Todo o código é escrito em inglês por questões de padronização. A idéia é seguir as convenções do
Python a medida do possível.

O código está disponível no Github no link https://github.com/ErFer7/Mini-Dungeon. Lá é possível
checar as alterações de cada versão.
'''

import sys
import os

from random import seed
from time import time_ns

import pygame
import core
import dungeons
import graphics
import physics
import UI

VERSION = "0.27.7" # Esta variável é usada apenas para a identificação da versão

seed(time_ns()) # Inicializa o gerador de números com o tempo como a seed

# Inicialização do pygame
pygame.display.init()
pygame.font.init()
pygame.mixer.init()

fps_clock = pygame.time.Clock() # Clock para o controle de tempo

display = pygame.display.set_mode(flags = pygame.FULLSCREEN) # Inicializa o display

# Inicializa os canais
music_channel = pygame.mixer.Channel(0)
sound_effects_channel = pygame.mixer.Channel(1)

music = pygame.mixer.Sound(os.path.join("Audio", "Music.wav")) # Inicializa a música

# Define o estado incial, o nível, e o nível máximo
game_state = core.GameState(core.State.MENU, 1, 10)

render_control = graphics.RenderControl() # Inicializa o controle de renderização

# Inicializa todas as interfaces de usuário
menu = UI.Menu((display.get_width(), display.get_height()), VERSION)
loading_screen = UI.LoadingScreen((display.get_width(), display.get_height()))
pause_screen = UI.PauseScreen((display.get_width(), display.get_height()))
HUD = UI.HUD((display.get_width(), display.get_height()))
game_over_screen = UI.GameOverScreen((display.get_width(), display.get_height()))
victory_screen = UI.VictoryScreen((display.get_width(), display.get_height()))
final_victory_screen = UI.FinalVictoryScreen((display.get_width(), display.get_height()))

def update_events():

    '''
    Atualiza os eventos do input
    '''

    events = pygame.event.get() # Obtém os eventos
    mouse_position = pygame.mouse.get_pos() # Obtém a posição do mouse

    # Adiciona um evendo "Nulo" para executar o loop (caso nõa tenha tenhum evento)
    if len(events) < 1:

        events.append(None)

    for event in events:

        if game_state.state == core.State.MENU: # No menu

            if event is not None:
                
                if event.type == pygame.KEYDOWN: # Caso uma tecla seja precionada

                    if event.key == pygame.K_ESCAPE or event.type == pygame.QUIT: # Sai do jogo

                        game_state.state = core.State.EXITING
                        break
                    elif event.key == pygame.K_RETURN: # Entra no jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(menu.selection_sound)

                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                if event.type == pygame.MOUSEBUTTONDOWN: # Caso um clique seja dado

                    if menu.check_buttons(mouse_position) == "Play": # Entra no jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(menu.selection_sound)

                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                    if menu.check_buttons(mouse_position) == "Quit": # Sai do jogo

                        game_state.state = core.State.EXITING
                        break
        elif game_state.state == core.State.INGAME: # No jogo

            if event is not None and event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE: # Pausa

                sound_effects_channel.stop()
                sound_effects_channel.play(pause_screen.selection_sound)

                game_state.state = core.State.PAUSED
                break

            player.update(event) # Atualiza os movimentos do jogador
        elif game_state.state == core.State.PAUSED: # Na pausa

            if event is not None:

                if event.type == pygame.KEYDOWN: # Caso uma tecla seja precionada

                    if event.key == pygame.K_ESCAPE: # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN: # Volta para o jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)

                        game_state.state = core.State.INGAME
                        render_control.update_all = True
                        break

                if event.type == pygame.MOUSEBUTTONDOWN: # Caso um clique seja dado

                    if pause_screen.check_buttons(mouse_position) == "Continue": # Volta para o jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        render_control.update_all = True
                        break

                    if pause_screen.check_buttons(mouse_position) == "Menu": # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.LOST: # Na derrota

            if event is not None:

                if event.type == pygame.KEYDOWN: # Caso uma tecla seja pressionada

                    if event.key == pygame.K_ESCAPE: # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN: # Recomeça o jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)

                        game_state.state = core.State.INGAME
                        break

                if event.type == pygame.MOUSEBUTTONDOWN: # Caso um clique seja dado

                    if game_over_screen.check_buttons(mouse_position) == "Restart": # Recomeça o jogo

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        break

                    if game_over_screen.check_buttons(mouse_position) == "Menu": # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.WON: # Na vitória

            if event is not None:

                if event.type == pygame.KEYDOWN: # Caso uma tecla seja pressionada

                    if event.key == pygame.K_ESCAPE: # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN: # Vai para o próximo nível

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)

                        game_state.state = core.State.INGAME
                        break

                if event.type == pygame.MOUSEBUTTONDOWN: # Caso um clique seja dado

                    if victory_screen.check_buttons(mouse_position) == "Next": # Vai para o próximo nível

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)

                        game_state.state = core.State.INGAME
                        break

                    if victory_screen.check_buttons(mouse_position) == "Menu": # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.FINISHED: # No fim do jogo (Vitória)

            if event is not None:

                if event.type == pygame.KEYDOWN: # Caso uma tecla seja pressionada

                    if event.key == pygame.K_ESCAPE: # Sai do jogo

                        game_state.state = core.State.EXITING
                        break
                    elif event.key == pygame.K_RETURN: # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(final_victory_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break

                if event.type == pygame.MOUSEBUTTONDOWN: # Caso um clique seja dado

                    if final_victory_screen.check_buttons(mouse_position) == "Menu": # Vai para o menu

                        sound_effects_channel.stop()
                        sound_effects_channel.play(final_victory_screen.selection_sound)

                        game_state.state = core.State.MENU
                        break

                    if final_victory_screen.check_buttons(mouse_position) == "Quit": # Sai do jogo

                        game_state.state = core.State.EXITING
                        break

def reset_game(rooms = None):

    '''
    Libera a memória da dungeon anterior
    '''

    if rooms is not None:

        for room_line in rooms:

            for room in room_line:

                room.delete()

        del rooms

# Define o volume e começa a música
music.set_volume(0.5)
music_channel.play(music, -1)

# Loop principal. Funciona enquanto o jogo não está no estado de saída
while game_state.state != core.State.EXITING:

    menu.update(display) # Exibe o menu

    while game_state.state == core.State.MENU: # Loop do menu

        update_events() # Atualiza os eventos

        pygame.display.update() # Atualiza o display
        fps_clock.tick(60) # Clock de 60 FPS

    if game_state.state == core.State.INGAME: # Carregamento do jogo

        loading_screen.update(display) # Exibe a tela de carregamento

        # Gera a dungeon
        player,     \
        rooms,      \
        room_index, \
        initial_monster_ammount = dungeons.generate_dungeon((display.get_width(), display.get_height()), 
                                                            game_state.level + 1,
                                                            game_state.level + 1)
        
        # Define que toda a tela deve ser atualizada
        render_control.update_all = True

    while game_state.state == core.State.INGAME or game_state.state == core.State.PAUSED: # Loop do jogo

        update_events() # Atualiza os eventos

        if game_state.state != core.State.PAUSED: # Caso o jogo não esteja pausado

            # Atualiza a física
            physics.update_physics(rooms,
                                   room_index,
                                   render_control,
                                   game_state,
                                   initial_monster_ammount,
                                   sound_effects_channel)

            # Atualiza a interface
            HUD.update(display,
                       player.life,
                       player.kill_count,
                       fps_clock.get_fps(),
                       "Sala: ({0}, {1})".format(room_index[0], room_index[1]),
                       initial_monster_ammount,
                       game_state.level,
                       game_state.max_level)

            # Renderiza a sala atual
            render_control.update_graphics(rooms[room_index[0]][room_index[1]], display)
        else:

            pause_screen.update(display) # Exibe e atualiza a tela de pausa

        fps_clock.tick(60) # Clock de 60 FPS

    while game_state.state == core.State.LOST: # Loop de derrota

        update_events() # Atualiza os eventos
        game_over_screen.update(display) # Exibe e atualiza a tela de derrota
        fps_clock.tick(60) # Clock de 60 FPS

    while game_state.state == core.State.WON: # Loop de vitória

        update_events() # Atualiza os eventos
        victory_screen.update(display) # Exibe e atualiza a tela de vitória
        fps_clock.tick(60) # Clock de 60 FPS

    while game_state.state == core.State.FINISHED: # Loop de fim de jogo (vitória)

        update_events() # Atualiza os eventos
        final_victory_screen.update(display) # Exibe e atualiza a tela de fim de jogo
        fps_clock.tick(60) # Clock de 60 FPS

    try:

        reset_game(rooms) # Deleta a dungeon caso ela exista
    except NameError:
        continue

pygame.quit() # Encerra o pygame
sys.exit() # Sai do jogo
