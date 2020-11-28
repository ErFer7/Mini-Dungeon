# -*- coding: utf-8 -*-

'''
Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
Github: https://github.com/ErFer7/Mini-Dungeon
'''

# Módulos
import sys

from enum import Enum
from random import seed
from time import time_ns

import psutil
import pygame
import core
import dungeons
import graphics
import physics
import UI

# Enumeradores
class GameState(Enum):

    '''
    Definição dos estados do jogo
    '''

    MENU = 1
    INGAME = 2
    PAUSED = 3
    WON = 4
    LOST = 5
    RESTARTING = 6
    EXITING = 7

# Constantes
VERSION = "0.24.1"

# ETAPA FINAL

# Efeitos sonoros
# Música
# Mais mapas

# EXTRAS

# Implementar itens diferentes
# Implementar monstros diferentes
# Baús
# Drops
# Slots
# Inventário

# Inicialização
seed(time_ns())

process = psutil.Process()

game_state = core.GameState(core.State.MENU, 1)
render_control = graphics.RenderControl()

pygame.display.init()
pygame.font.init()

fps_clock = pygame.time.Clock()
display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

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

    events = pygame.event.get()
    mouse_position = pygame.mouse.get_pos()

    if len(events) < 1:

        events.append(None)

    for event in events:

        if game_state.state == core.State.MENU:

            if event is not None:
            
                if event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

                        game_state.state = core.State.EXITING
                        break
                    elif event.key == pygame.K_RETURN:

                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if menu.check_buttons(mouse_position) == "Play":

                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                    if menu.check_buttons(mouse_position) == "Quit":

                        game_state.state = core.State.EXITING
                        break
        elif game_state.state == core.State.INGAME:

            if event is not None and event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                game_state.state = core.State.PAUSED
                break

            player.update(event)
        elif game_state.state == core.State.PAUSED:

            if event is not None:
                
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                    game_state.state = core.State.INGAME
                    render_control.update_all = True
                    break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if pause_screen.check_buttons(mouse_position) == "Continue":

                        game_state.state = core.State.INGAME
                        render_control.update_all = True
                        break

                    if pause_screen.check_buttons(mouse_position) == "Menu":

                        game_state.state = core.State.MENU
                        render_control.update_all = True
                        break
        elif game_state.state == core.State.LOST:

            if event is not None:

                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                    game_state.state = core.State.MENU
                    break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if game_over_screen.check_buttons(mouse_position) == "Restart":

                        game_state.state = core.State.INGAME
                        break

                    if game_over_screen.check_buttons(mouse_position) == "Menu":

                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.WON:

            if event is not None:

                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                    game_state.state = core.State.MENU
                    break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if victory_screen.check_buttons(mouse_position) == "Next":

                        game_state.state = core.State.INGAME
                        break

                    if victory_screen.check_buttons(mouse_position) == "Menu":

                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.FINISHED:

            if event is not None:

                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                    game_state.state = core.State.MENU
                    break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if final_victory_screen.check_buttons(mouse_position) == "Menu":

                        game_state.state = core.State.MENU
                        break

                    if final_victory_screen.check_buttons(mouse_position) == "Quit":

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

# Loop principal
while game_state.state != core.State.EXITING:

    menu.update(display)

    # Loop do menu
    while game_state.state == core.State.MENU:

        # MENU
        update_events()

        pygame.display.update()
        fps_clock.tick(60)

    if game_state.state == core.State.INGAME:

        loading_screen.update(display)
        player, rooms, room_index, initial_monster_ammount = dungeons.generate_dungeon([display.get_width(), display.get_height()], game_state.level + 1, game_state.level + 1)
        render_control.update_all = True

    while game_state.state == core.State.INGAME or game_state.state == core.State.PAUSED:

        update_events()

        if game_state.state != core.State.PAUSED:

            physics.update_physics(rooms, room_index, render_control, game_state, initial_monster_ammount)

            HUD.update(display, player.life, player.kill_count, fps_clock.get_fps(),    \
                        "Sala: ({0}, {1})".format(room_index[0], room_index[1]),        \
                        process.memory_info()[0] / 1000, initial_monster_ammount)

            render_control.update_graphics(rooms[room_index[0]][room_index[1]], display)
        else:

            pause_screen.update(display)

        fps_clock.tick(60)

    while game_state.state == core.State.LOST:

        update_events()
        game_over_screen.update(display)
        fps_clock.tick(60)

    while game_state.state == core.State.WON:

        update_events()
        victory_screen.update(display)
        fps_clock.tick(60)

    while game_state.state == core.State.FINISHED:

        update_events()
        final_victory_screen.update(display)
        fps_clock.tick(60)

    try:

        reset_game(rooms)
    except NameError:
        continue

pygame.quit()
sys.exit()