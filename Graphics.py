# -*- coding: utf-8 -*-

import os
import pygame

class StoneWallSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall_0.png")), (256, 256))
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

        if floorType == '<':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 90)
        elif floorType == '>':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), -90)
        elif floorType == '^':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32))
        elif floorType == 'v':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 180)
        elif floorType == 'q':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32))
        elif floorType == 'w':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, False)
        elif floorType == 'e':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), False, True)
        elif floorType == 'r':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, True)
        elif floorType == 't':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32))
        elif floorType == 'y':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), -90)
        elif floorType == 'u':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 180)
        elif floorType == 'i':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 90)
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor.png")), (32, 32))

        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class WallSprite(pygame.sprite.Sprite):

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY

class DoorSprite(pygame.sprite.Sprite):

    direction = 0

    def __init__(self, posX, posY, direction):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Door.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self.direction = direction

class PlayerSprite(pygame.sprite.Sprite):

    _direction = 0
    _cHOrientation = 0

    def __init__(self, posX, posY):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = posX
        self.rect.y = posY
        self._direction = 1
    
    def update(self, posX, posY, hOrientation):

        self.rect.x = posX
        self.rect.y = posY

        if hOrientation != 0 and self._cHOrientation != hOrientation:

            self._cHOrientation = hOrientation

            if hOrientation < 0 and self._direction == 1:

                self.image = pygame.transform.flip(self.image, True, False)
                self._direction = -1
            elif self._direction == -1:

                self.image = pygame.transform.flip(self.image, True, False)
                self._direction = 1