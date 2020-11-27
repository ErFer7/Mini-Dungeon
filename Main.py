# -*- coding: utf-8 -*-

'''
Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
Github: https://github.com/ErFer7/Mini-Dungeon
'''

# Módulos
import os
import sys

from enum import Enum
from random import seed
from time import time_ns

import psutil
import pygame
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
VERSION = "0.20.1"

# ETAPA FINAL

# Implementar fim de jogo
# Implementar progressão de fases e vitória
# Implementar geração de monstros dinâmica
# Poções de vida
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

# Funções
def update_events():

    '''
    Atualiza os eventos do input
    '''

    global game_state

    events = pygame.event.get()
    mouse_position = pygame.mouse.get_pos()

    if len(events) < 1:

        events.append(None)

    for event in events:

        if event is not None:

            if game_state == GameState.MENU:

                if event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

                        game_state = GameState.EXITING
                        break
                    elif event.key == pygame.K_RETURN:

                        game_state = GameState.INGAME
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if menu.check_buttons(mouse_position) == "Play":

                        game_state = GameState.INGAME
                        break

                    if menu.check_buttons(mouse_position) == "Quit":

                        game_state = GameState.EXITING
                        break

        if game_state == GameState.INGAME:

            if event is not None and event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                game_state = GameState.PAUSED
                break

            player.update(event)
        elif game_state == GameState.PAUSED:

            if event is not None and event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                game_state = GameState.INGAME
                render_control.update_all = True
                break

            if event is not None and event.type == pygame.MOUSEBUTTONDOWN:

                if pause_screen.check_buttons(mouse_position) == "Continue":

                    game_state = GameState.INGAME
                    render_control.update_all = True
                    break

                if pause_screen.check_buttons(mouse_position) == "Menu":

                    game_state = GameState.MENU
                    render_control.update_all = True
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

# Inicialização
seed(time_ns())

process = psutil.Process()
game_state = GameState.MENU
render_control = graphics.RenderControl()

pygame.display.init()
pygame.font.init()

fps_clock = pygame.time.Clock()

font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 15)

display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

menu = UI.Menu((display.get_width(), display.get_height()), VERSION)
loading_screen = UI.LoadingScreen((display.get_width(), display.get_height()))
pause_screen = UI.PauseScreen((display.get_width(), display.get_height()))
HUD = UI.HUD((display.get_width(), display.get_height()))

# Loop principal
while game_state != GameState.EXITING:

    menu.update(display)

    # Loop do menu
    while game_state == GameState.MENU:

        # MENU
        update_events()

        pygame.display.update()
        fps_clock.tick(60)

    if game_state == GameState.INGAME:

        loading_screen.update(display)
        player, rooms, room_index, initial_monster_ammount = dungeons.generate_dungeon([display.get_width(), display.get_height()], 5, 5)
        render_control.update_all = True

    while game_state == GameState.INGAME or game_state == GameState.PAUSED:

        #update_UI()
        update_events()

        if game_state != GameState.PAUSED:

            physics.update_physics(rooms, room_index, render_control)

            HUD.update(display, player.life,                                        \
                        "{0:.2f} FPS".format(fps_clock.get_fps()),                  \
                        "Sala: ({0}, {1})".format(room_index[0], room_index[1]),    \
                        "Memória: {0} kB".format(process.memory_info()[0] / 1000))

            render_control.update_graphics(rooms[room_index[0]][room_index[1]], display)
        else:

            pause_screen.update(display)

        fps_clock.tick(60)

    reset_game(rooms)

pygame.quit()
sys.exit()