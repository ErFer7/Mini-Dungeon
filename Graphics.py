# -*- coding: utf-8 -*-

import os
import pygame

class StoneWallSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.image.load(os.path.join("Sprites", "Stone wall.png"))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class ButtonSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY, width, height, *color):

        super().__init__()
        self.image = pygame.Surface([width, height])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill(color)

# EM TESTES
class FloorSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY, floorType):

        super().__init__()

        if floorType == "<":

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_100.png")), (32, 32))
        elif floorType == ">":

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_102.png")), (32, 32))
        elif floorType == "^":

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_86.png")), (32, 32))
        elif floorType == "v":

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_108.png")), (32, 32))
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_108.png")), (32, 32))

        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class WallSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_17.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class DoorSprite(pygame.sprite.Sprite):

    direction = 0

    def __init__(self, posX, posY, direction):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Tileset_39.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.direction = direction

class PlayerSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.Surface([24, 24])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill((255, 0, 255))
    
    def update(self, posX, posY):

        self.rect.x = posX
        self.rect.y = posY