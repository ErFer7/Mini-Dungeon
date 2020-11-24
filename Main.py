# -*- coding: utf-8 -*-

# Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
# Github: https://github.com/ErFer7/Mini-Dungeon

# Módulos
import os
import sys
import psutil
#import objgraph

from enum import Enum
from math import ceil
from random import seed
from time import time_ns

import pygame
import dungeons
import graphics
import entities
import physics

# Enumeradores
class GameState(Enum):

    MENU = 1
    INGAME = 2
    PAUSED = 3
    RESTARTING = 4
    EXITING = 5

# Constantes
VERSION = "0.15.1"

# Variáveis globais
game_state = GameState.MENU
mouse_position_X: int
mouse_position_Y: int
rooms: list
player: entities.Player
render_control: graphics.RenderControl

# Funções
def update_events(player = None):

    global game_state
    global mouse_position_X
    global mouse_position_Y

    events = pygame.event.get()

    mouse_position_X = pygame.mouse.get_pos()[0]
    mouse_position_Y = pygame.mouse.get_pos()[1]

    for event in events:

        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

            game_state = GameState.EXITING
            break

        if game_state == GameState.MENU:

            if event.type == pygame.MOUSEBUTTONDOWN and (mouse_position_X >= (display.get_width() - 400) / 2 and mouse_position_X <= (display.get_width() + 400) / 2) and (mouse_position_Y >= (display.get_height() - 125) / 2 and mouse_position_Y <= (display.get_height() + 125) / 2):

                game_state = GameState.INGAME
                break
            
            if event.type == pygame.MOUSEBUTTONDOWN and (mouse_position_X >= (display.get_width() - 400) / 2 and mouse_position_X <= (display.get_width() + 400) / 2) and (mouse_position_Y >= (display.get_height() * 1.5 - 125) / 2 and mouse_position_Y <= (display.get_height() * 1.5 + 125) / 2):

                game_state = GameState.EXITING
                break
        elif game_state == GameState.INGAME:

            player.control(event)

def build_menu():

    sprites = pygame.sprite.RenderPlain()
    
    for i in range(ceil(display.get_height() / 256)):

        for j in range(ceil(display.get_width() / 256)):

            sprites.add(graphics.BackgroundSprite(j * 256, i * 256))

    play_button_border = graphics.ButtonSprite((display.get_width() - 400) / 2, (display.get_height() - 125) / 2, 400, 125, (255, 223, 0))
    play_button = graphics.ButtonSprite((display.get_width() - 380) / 2, (display.get_height() - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((play_button_border, play_button))

    quit_button_border = graphics.ButtonSprite((display.get_width() - 400) / 2, (display.get_height() * 1.5 - 125) / 2, 400, 125, (255, 223, 0))
    quit_button = graphics.ButtonSprite((display.get_width() - 380) / 2, (display.get_height() * 1.5 - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((quit_button_border, quit_button))

    version_text = font.render("V {0}".format(VERSION), False, (255, 255, 255))
    title_text = title_font.render("MINI DUNGEON", False, (255, 223, 0))
    title_shadow_text = title_font_shadow.render("MINI DUNGEON", False, (10, 10, 10))
    play_txt = title_font.render("JOGAR", False, (255, 223, 0))
    quit_text = title_font.render("SAIR", False, (255, 223, 0))

    sprites.draw(display)
    
    display.blit(version_text, (0, 0))
    display.blit(title_shadow_text, ((display.get_width() - title_shadow_text.get_rect().width) / 2 - 10, (display.get_height() * 0.5 - title_shadow_text.get_rect().height) / 2))
    display.blit(title_text, ((display.get_width() - title_text.get_rect().width) / 2, (display.get_height() * 0.5 - title_text.get_rect().height) / 2))
    display.blit(play_txt, ((display.get_width() - play_txt.get_rect().width) / 2, (display.get_height() - play_txt.get_rect().height) / 2))
    display.blit(quit_text, ((display.get_width() - quit_text.get_rect().width) / 2, (display.get_height() * 1.5 - quit_text.get_rect().height) / 2))

    pygame.display.update()

def build_loading_screen():

    display.fill((10, 10, 10))

    loading_text = title_font.render("Carregando...", False, (255, 223, 0))
    display.blit(loading_text, ((display.get_width() - loading_text.get_rect().width) / 2, (display.get_height() - loading_text.get_rect().height) / 2))

    pygame.display.update()

# Inicialização
#seed(time_ns())
seed(2)

process = psutil.Process()
render_control = graphics.RenderControl(True)

pygame.init()

fps_clock = pygame.time.Clock()

title_font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
title_font_shadow = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 15)

display = pygame.display.set_mode(flags = pygame.FULLSCREEN)
UI_display = pygame.Surface([400, 120])

# Loop principal
while game_state != GameState.EXITING:

    # Constrói o menu
    build_menu()

    # Loop do menu
    while game_state == GameState.MENU:
        
        # MENU
        update_events()

        pygame.display.update()
        fps_clock.tick(60)
    
    if game_state == GameState.INGAME:
        
        build_loading_screen()
        # 25 é o máximo
        player, rooms, room_index = dungeons.generate_dungeon([display.get_width(), display.get_height()], 2, 2)
        display.fill((10, 10, 10))

    while game_state == GameState.INGAME:
        
        UI_display.fill((255, 10, 10))
        display.blit(UI_display, (0, 0))
        display.blit(font.render("{0:.2f} FPS".format(fps_clock.get_fps()), False, (255, 255, 255)), (0, 0))
        display.blit(font.render("Player Pos: ({0:.2f}, {1:.2f})".format(player.position[0], player.position[1]), False, (255, 255, 255)), (0, 20))
        display.blit(font.render("Player Vel: ({0:.2f}, {1:.2f})".format(player.velocity[0], player.velocity[1]), False, (255, 255, 255)), (0, 40))
        display.blit(font.render("Room: ({0}, {1})".format(room_index[0], room_index[1]), False, (255, 255, 255)), (0, 60))
        display.blit(font.render("Memory: {0} kB".format(process.memory_info()[0] / 1000), False, (255, 255, 255)), (0, 80))

        update_events(player)
        physics.update_physics(rooms, room_index, render_control)
        render_control.update_graphics(rooms[room_index[0]][room_index[1]], display)
        #print("----------------------------")
        #objgraph.show_most_common_types(limit = 50)
        fps_clock.tick(60)

    #obj = objgraph.by_type("FloorSprite")
    #objgraph.show_backrefs(obj, max_depth=10)

pygame.quit()
sys.exit()