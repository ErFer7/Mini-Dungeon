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

# class Floor(pygame.sprite.Sprite):

#     def __init__(self, posX, posY, floorType):

#         super().__init__()

#         if floorType == "╔":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Top left corner.png"))
#         elif floorType == "╗":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Top right corner.png"))
#         elif floorType == "╚":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Botton left corner.png"))
#         elif floorType == "╝":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Botton right corner.png"))
#         elif floorType == "<":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Left.png"))
#         elif floorType == ">":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Right.png"))
#         elif floorType == "^":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Top.png"))
#         elif floorType == "v":

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor - Botton.png"))
#         else:

#             self.image = pygame.image.load(os.path.join("Sprites", "Floor.png"))

#         self.rect = self.image.get_rect()
#         self.rect.x = posX
#         self.rect.y = posY

class FloorSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY, floorType):

        super().__init__()
        self.image = pygame.Surface([64, 64])

        if floorType == "╔":

            self.image.fill((0, 255, 0))
        elif floorType == "╗":

            self.image.fill((0, 255, 0))
        elif floorType == "╚":

            self.image.fill((0, 255, 0))
        elif floorType == "╝":

            self.image.fill((0, 255, 0))
        elif floorType == "<":

            self.image.fill((0, 0, 255))
        elif floorType == ">":

            self.image.fill((0, 0, 255))
        elif floorType == "^":

            self.image.fill((0, 0, 255))
        elif floorType == "v":

            self.image.fill((0, 0, 255))
        elif floorType == "┘":

            self.image.fill((0, 0, 125))
        elif floorType == "└":

            self.image.fill((0, 0, 125))
        elif floorType == "┐":

            self.image.fill((0, 0, 125))
        elif floorType == "┌":

            self.image.fill((0, 0, 125))
        else:

            self.image.fill((125, 125, 125))

        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class WallSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.Surface([64, 64])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill((255, 255, 255))

class DoorSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.Surface([64, 64])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill((255, 0, 0))

class PlayerSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.Surface([64, 64])
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.image.fill((255, 0, 255))
    
    def update(self, posX, posY):

        self.rect.x = posX
        self.rect.y = posY