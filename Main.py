# V 0.0.5
# Escrito por Eric Fernandes Evaristo para a discplina de Programação OOP I da UFSC.
# Github: https://github.com/ErFer7/Mini-Dungeon

import os
import sys
import pygame
# import DungeonManager

# Inicialização
pygame.init()
fpsClock = pygame.time.Clock()
myfont = pygame.font.Font(os.path.join("Fonts", "joystix monospace.ttf"), 30)

display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

wallImg = pygame.image.load(os.path.join("Sprites", "Stone wall.png"))

textsurface = myfont.render("MINI DUNGEON - V 0.0.5", False, (0, 0, 0))
red = (255, 0, 0)
rect = pygame.Rect(200, 150, 100, 50)

while True:

    events = pygame.event.get()

    for event in events:

        if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE or event.type == pygame.QUIT:

            print("Display finalizado")
            pygame.quit()
            sys.exit()
    
    mousePos = pygame.mouse.get_pos()

    #display.fill((255, 255, 255))
    display.blit(wallImg, mousePos)
    display.blit(textsurface,(0,0))
    pygame.display.update()
    fpsClock.tick(60)