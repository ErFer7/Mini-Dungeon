import os
import pygame

class StoneWall(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.image.load(os.path.join("Sprites", "Stone wall.png"))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class Button(pygame.sprite.Sprite):

    def __init__(self, posX, posY, width, height, *color):

        super().__init__()
        self.image = pygame.Surface([width, height])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill(color)