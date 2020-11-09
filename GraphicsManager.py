import os
import pygame

# Definição as sprites
class StoneWall(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.image.load(os.path.join("Sprites", "Stone wall.png"))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY