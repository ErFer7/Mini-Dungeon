import pygame
import DungeonManager

pygame.display.init()

DungeonManager.DungeonGenerator(100, 100)

if pygame.display.get_init():

    pygame.display.set_mode(flags = pygame.FULLSCREEN)
    print("Display inicializado")
else:

    print("Falha no display")

pygame.display.quit()