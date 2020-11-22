# -*- coding: utf-8 -*-

import os
import pygame

class StoneWallSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall_0.png")), (256, 256))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class ButtonSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y, width, height, *color):

        super().__init__()
        self.image = pygame.Surface([width, height])
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self.image.fill(color)

class FloorSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y, floor_type):

        super().__init__()

        if floor_type == '<':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 90)
        elif floor_type == '>':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), -90)
        elif floor_type == '^':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32))
        elif floor_type == 'v':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 180)
        elif floor_type == 'q':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32))
        elif floor_type == 'w':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, False)
        elif floor_type == 'e':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), False, True)
        elif floor_type == 'r':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, True)
        elif floor_type == 't':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32))
        elif floor_type == 'y':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), -90)
        elif floor_type == 'u':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 180)
        elif floor_type == 'i':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 90)
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor.png")), (32, 32))

        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class WallSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class DoorSprite(pygame.sprite.Sprite):

    direction: int

    def __init__(self, pos_x, pos_y, direction):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Door.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self.direction = direction

class PlayerSprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_15.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self._old_horizontal_orientation = 1
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        self.rect.x = pos_x
        self.rect.y = pos_y

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation

class MonsterSprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self._old_horizontal_orientation = 1
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        self.rect.x = pos_x
        self.rect.y = pos_y

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation