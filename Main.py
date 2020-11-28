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

from enum import Enum
from random import seed
from time import time_ns

import pygame
import core
import dungeons
import graphics
import physics
import UI

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

VERSION = "0.27.2"  # Esta variável é usada apenas para a identificação da versão

seed(time_ns()) # Inicializa o gerador de números com o tempo como a seed

game_state = core.GameState(core.State.MENU, 1, 10)
render_control = graphics.RenderControl()

pygame.display.init()
pygame.font.init()
pygame.mixer.init()

fps_clock = pygame.time.Clock()
display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

music_channel = pygame.mixer.Channel(0)
sound_effects_channel = pygame.mixer.Channel(1)

music = pygame.mixer.Sound(os.path.join("Audio", "Music.wav"))

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

                        sound_effects_channel.stop()
                        sound_effects_channel.play(menu.selection_sound)
                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if menu.check_buttons(mouse_position) == "Play":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(menu.selection_sound)
                        game_state.state = core.State.INGAME
                        game_state.level = 1
                        break

                    if menu.check_buttons(mouse_position) == "Quit":

                        game_state.state = core.State.EXITING
                        break
        elif game_state.state == core.State.INGAME:

            if event is not None and event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:

                sound_effects_channel.stop()
                sound_effects_channel.play(pause_screen.selection_sound)
                game_state.state = core.State.PAUSED
                break

            player.update(event)
        elif game_state.state == core.State.PAUSED:

            if event is not None:
                
                if event.type == pygame.KEYDOWN:
                    
                    if event.key == pygame.K_ESCAPE:
                        
                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        render_control.update_all = True
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if pause_screen.check_buttons(mouse_position) == "Continue":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        render_control.update_all = True
                        break

                    if pause_screen.check_buttons(mouse_position) == "Menu":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(pause_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.LOST:

            if event is not None:

                if event.type == pygame.KEYDOWN:
                    
                    if event.key == pygame.K_ESCAPE:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if game_over_screen.check_buttons(mouse_position) == "Restart":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        break

                    if game_over_screen.check_buttons(mouse_position) == "Menu":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(game_over_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.WON:

            if event is not None:

                if event.type == pygame.KEYDOWN:
                    
                    if event.key == pygame.K_ESCAPE:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
                    elif event.key == pygame.K_RETURN:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if victory_screen.check_buttons(mouse_position) == "Next":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)
                        game_state.state = core.State.INGAME
                        break

                    if victory_screen.check_buttons(mouse_position) == "Menu":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(victory_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break
        elif game_state.state == core.State.FINISHED:

            if event is not None:

                if event.type == pygame.KEYDOWN:
                    
                    if event.key == pygame.K_ESCAPE:

                        game_state.state = core.State.EXITING
                        break
                    elif event.key == pygame.K_RETURN:

                        sound_effects_channel.stop()
                        sound_effects_channel.play(final_victory_screen.selection_sound)
                        game_state.state = core.State.MENU
                        break

                if event.type == pygame.MOUSEBUTTONDOWN:

                    if final_victory_screen.check_buttons(mouse_position) == "Menu":

                        sound_effects_channel.stop()
                        sound_effects_channel.play(final_victory_screen.selection_sound)
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

music.set_volume(0.5)
music_channel.play(music, -1)

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

            physics.update_physics(rooms, room_index, render_control, game_state, initial_monster_ammount, sound_effects_channel)

            HUD.update(display, player.life, player.kill_count, fps_clock.get_fps(),    \
                        "Sala: ({0}, {1})".format(room_index[0], room_index[1]),        \
                        initial_monster_ammount, game_state.level, game_state.max_level)

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