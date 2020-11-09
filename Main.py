# V 0.0.7
# Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
# Github: https://github.com/ErFer7/Mini-Dungeon

import os
import sys
import pygame
# import DungeonManager
import GraphicsManager

from enum import Enum
from math import ceil

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

# Funções
def UpdateEvents():

    global gameState
    global mousePosX
    global mousePosY

    events = pygame.event.get()

    mousePosX = pygame.mouse.get_pos()[0]
    mousePosY = pygame.mouse.get_pos()[1]

    for event in events:

        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

            gameState = GameState.EXITING

        #if event.type == pygame.MOUSEBUTTONDOWN and (mousePosX >= (display.get_width() - 400) / 2 and mousePosX <= (display.get_width() + 400) / 2) and (mousePosY >= (display.get_height() - 125) / 2 and mousePosY <= (display.get_height() + 125) / 2):

            #gameState = GameState.INGAME
        
        if event.type == pygame.MOUSEBUTTONDOWN and (mousePosX >= (display.get_width() - 400) / 2 and mousePosX <= (display.get_width() + 400) / 2) and (mousePosY >= (display.get_height() * 1.5 - 125) / 2 and mousePosY <= (display.get_height() * 1.5 + 125) / 2):

            gameState = GameState.EXITING

def BuildMenu():
    sprites = pygame.sprite.RenderPlain()
    
    for i in range(ceil(display.get_height() / 256)):

        for j in range(ceil(display.get_width() / 256)):

            sprites.add(GraphicsManager.StoneWall(j * 256, i * 256))

    playButtonBorder = GraphicsManager.Button((display.get_width() - 400) / 2, (display.get_height() - 125) / 2, 400, 125, (255, 223, 0))
    playButton = GraphicsManager.Button((display.get_width() - 380) / 2, (display.get_height() - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((playButtonBorder, playButton))

    quitButtonBorder = GraphicsManager.Button((display.get_width() - 400) / 2, (display.get_height() * 1.5 - 125) / 2, 400, 125, (255, 223, 0))
    quitButton = GraphicsManager.Button((display.get_width() - 380) / 2, (display.get_height() * 1.5 - 105) / 2, 380, 105, (10, 10, 10))
    sprites.add((quitButtonBorder, quitButton))

    versionTxt = font.render("V 0.0.7", False, (255, 255, 255))
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

# Inicialização
pygame.init()

fpsClock = pygame.time.Clock()

titleFont = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
titleFontShadow = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 15)

display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

# Loop principal
while gameState != GameState.EXITING:

    BuildMenu()

    while gameState == GameState.MENU:
        
        # MENU
        UpdateEvents()

        pygame.display.update()
        fpsClock.tick(60)
    
    while gameState == GameState.INGAME:

        # GAMEPLAY
        pygame.display.update()
        fpsClock.tick(60)

pygame.quit()
sys.exit()