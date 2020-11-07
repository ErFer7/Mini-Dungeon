# V 0.0.3

import sys
import pygame
# import DungeonManager

pygame.init()
display = pygame.display.set_mode(flags = pygame.FULLSCREEN)

myfont = pygame.font.SysFont('Arial', 30)
textsurface = myfont.render("MINI DUNGEON - V 0.0.3", False, (0, 0, 0))
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

    display.fill((255, 255, 255))
    surf = pygame.Surface((100, 50))
    pygame.draw.rect(surf, red, rect)
    display.blit(surf, mousePos)
    display.blit(textsurface,(0,0))
    pygame.display.update()
    pygame.time.delay(1)