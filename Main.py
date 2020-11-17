# -*- coding: utf-8 -*-

# V 0.2
# Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
# Github: https://github.com/ErFer7/Mini-Dungeon

# Módulos
import os
import sys
import pygame
import Dungeons
import Graphics
import Entities
import Physics

from enum import Enum
from math import ceil
from random import seed
from time import time_ns

# Enumeradores
class GameState(Enum):

    MENU = 1
    INGAME = 2
    RESTARTING = 3
    EXITING = 4

# Variáveis globais
gameState = GameState.MENU
mousePosX = 0
mousePosY = 0
rooms = []

# Funções
def UpdateEvents(player = None):

    global gameState
    global mousePosX
    global mousePosY

    events = pygame.event.get()

    mousePosX = pygame.mouse.get_pos()[0]
    mousePosY = pygame.mouse.get_pos()[1]

    for event in events:

        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

            gameState = GameState.EXITING

        if gameState == GameState.MENU:

            if event.type == pygame.MOUSEBUTTONDOWN and (mousePosX >= (display.get_width() - 400) / 2 and mousePosX <= (display.get_width() + 400) / 2) and (mousePosY >= (display.get_height() - 125) / 2 and mousePosY <= (display.get_height() + 125) / 2):

                gameState = GameState.INGAME
            
            if event.type == pygame.MOUSEBUTTONDOWN and (mousePosX >= (display.get_width() - 400) / 2 and mousePosX <= (display.get_width() + 400) / 2) and (mousePosY >= (display.get_height() * 1.5 - 125) / 2 and mousePosY <= (display.get_height() * 1.5 + 125) / 2):

                gameState = GameState.EXITING
        elif gameState == GameState.INGAME:

            player.Control(event)

def BuildMenu():

    sprites = pygame.sprite.RenderPlain()
    
    for i in range(ceil(display.get_height() / 256)):

        for j in range(ceil(display.get_width() / 256)):

            sprites.add(Graphics.StoneWallSprite(j * 256, i * 256))

    playButtonBorder = Graphics.ButtonSprite((display.get_width() - 400) / 2, (display.get_height() - 125) / 2, 400, 125, (255, 223, 0))
    playButton = Graphics.ButtonSprite((display.get_width() - 380) / 2, (display.get_height() - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((playButtonBorder, playButton))

    quitButtonBorder = Graphics.ButtonSprite((display.get_width() - 400) / 2, (display.get_height() * 1.5 - 125) / 2, 400, 125, (255, 223, 0))
    quitButton = Graphics.ButtonSprite((display.get_width() - 380) / 2, (display.get_height() * 1.5 - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((quitButtonBorder, quitButton))

    versionTxt = font.render("V 0.2", False, (255, 255, 255))
    titleTxt = titleFont.render("MINI DUNGEON", False, (255, 223, 0))
    titleShadowTxt = titleFontShadow.render("MINI DUNGEON", False, (10, 10, 10))
    playTxt = titleFont.render("JOGAR", False, (255, 223, 0))
    quitTxt = titleFont.render("SAIR", False, (255, 223, 0))

    sprites.draw(display)
    
    display.blit(versionTxt, (0, 0))
    display.blit(titleShadowTxt, ((display.get_width() - titleShadowTxt.get_rect().width) / 2 - 10, (display.get_height() * 0.5 - titleShadowTxt.get_rect().height) / 2))
    display.blit(titleTxt, ((display.get_width() - titleTxt.get_rect().width) / 2, (display.get_height() * 0.5 - titleTxt.get_rect().height) / 2))
    display.blit(playTxt, ((display.get_width() - playTxt.get_rect().width) / 2, (display.get_height() - playTxt.get_rect().height) / 2))
    display.blit(quitTxt, ((display.get_width() - quitTxt.get_rect().width) / 2, (display.get_height() * 1.5 - quitTxt.get_rect().height) / 2))

    pygame.display.update()

def BuildLoadingScreen():

    display.fill((10, 10, 10))

    loadingTxt = titleFont.render("Carregando...", False, (255, 223, 0))
    display.blit(loadingTxt, ((display.get_width() - loadingTxt.get_rect().width) / 2, (display.get_height() - loadingTxt.get_rect().height) / 2))

    pygame.display.update()

# Inicialização
seed(time_ns())

pygame.init()

fpsClock = pygame.time.Clock()

titleFont = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
titleFontShadow = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 15)

display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

# Loop principal
while gameState != GameState.EXITING:

    # Constrói o menu
    BuildMenu()

    # Loop do menu
    while gameState == GameState.MENU:
        
        # MENU
        UpdateEvents()

        pygame.display.update()
        fpsClock.tick(60)
    
    if gameState == GameState.INGAME:
        
        BuildLoadingScreen()
        rooms, rIndex = Dungeons.GenerateDungeon([display.get_width(), display.get_height()], 2, 2)
        display.fill((10, 10, 10))

    while gameState == GameState.INGAME:
        
        display.fill((0, 0, 0))
        display.blit(font.render("{0:.2f} FPS".format(fpsClock.get_fps()), False, (255, 255, 255)), (0, 0))

        UpdateEvents(rooms[rIndex[0]][rIndex[1]].entities[0])
        Physics.UpdatePhysics(rooms[rIndex[0]][rIndex[1]].entities, rooms[rIndex[0]][rIndex[1]], rIndex)

        rooms[rIndex[0]][rIndex[1]].sprites.draw(display)
        rooms[rIndex[0]][rIndex[1]].collisionSprites.draw(display)
        rooms[rIndex[0]][rIndex[1]].triggerSprites.draw(display)

        for entity in rooms[rIndex[0]][rIndex[1]].entities:

            entity.sprites.update(entity.position[0], entity.position[1])

        rooms[rIndex[0]][rIndex[1]].entities[0].sprites.draw(display)

        pygame.display.update()

        fpsClock.tick(60)

pygame.quit()
sys.exit()