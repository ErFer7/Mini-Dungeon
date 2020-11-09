# V 0.0.6
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

# Funções
def UpdateEvents():

    global gameState

    events = pygame.event.get()

    for event in events:

        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

            gameState = GameState.EXITING

# Variáveis globais
gameState = GameState.MENU

# Inicialização
pygame.init()
fpsClock = pygame.time.Clock()
titleFont = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
titleFontShadow = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 80)
font = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 15)
display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

# Loop principal
while gameState != GameState.EXITING:

    # Constroi o menu
    stoneWallBackground = pygame.sprite.RenderPlain()
    for i in range(ceil(display.get_height() / 256)):

        for j in range(ceil(display.get_width() / 256)):

            stoneWallBackground.add(GraphicsManager.StoneWall(j * 256, i * 256))

    version = font.render("V 0.0.6", False, (255, 255, 255))
    title = titleFont.render("MINI DUNGEON", False, (255, 223, 0))
    titleShadow = titleFontShadow.render("MINI DUNGEON", False, (10, 10, 10))

    stoneWallBackground.draw(display)
    display.blit(version, (0, 0))
    display.blit(titleShadow, ((display.get_width() - titleShadow.get_rect().width) / 2 - 10, (display.get_height() * 0.5 - titleShadow.get_rect().height) / 2))
    display.blit(title, ((display.get_width() - title.get_rect().width) / 2, (display.get_height() * 0.5 - title.get_rect().height) / 2))
    pygame.display.flip()

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