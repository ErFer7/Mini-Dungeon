# -*- coding: utf-8 -*-

import os

from math import sin
from random import randint

import pygame

class RenderControl():

    update_all: bool

    def __init__(self):

        self.update_all = False

    def update_graphics(self, room, display):

        if self.update_all:

            display.fill((20, 20, 20))

            room.sprites.draw(display)
            room.collision_sprites.draw(display)
            room.collision_sprites.update()
            room.trigger_sprites.draw(display)

            self.update_all = False
        else:

            for key in room.entities:

                overlap_group = pygame.sprite.RenderPlain()

                for group in [room.collision_sprites, room.trigger_sprites, room.sprites]:
                    
                    overlap = pygame.sprite.spritecollide(room.entities[key].sprites.sprites()[0].render_area, group, False)

                    if overlap != None:

                        for sprite in overlap:

                            overlap_group.add(sprite)

                overlap_group.draw(display)
                overlap_group.empty()

            for key in room.entities:

                room.entities[key].sprites.sprites()[0].entity_sprites.draw(display)

        pygame.display.update()

class BackgroundSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y):

        super().__init__()

        random_number = 0

        if randint(0, 100) >= 90:

            random_number = randint(1, 7)

        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall_{0}.png".format(random_number))), (256, 256))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class RectangleSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y, width, height, *color):

        super().__init__()
        self.image = pygame.Surface((width, height))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self.image.fill(color)
    
    def update(self, pos_x, pos_y, width, height):

        self.image = pygame.transform.scale(self.image, (width, height))
        self.rect.x = pos_x
        self.rect.y = pos_y

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

    def __init__(self, pos_x, pos_y, wall_type):

        super().__init__()

        if wall_type == '#':
            
            random_number = 0

            if randint(0, 100) >= 90:

                random_number = randint(1, 12)

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall_{0}.png".format(random_number))), (32, 32))
        elif wall_type == '_':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top.png")), (32, 32))
        elif wall_type == '$':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Left.png")), (32, 32))
        elif wall_type == '%':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Right.png")), (32, 32))
        elif wall_type == '@':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Left.png")), (32, 32))
        elif wall_type == '+':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Left.png")), (32, 32)), False, True)
        elif wall_type == '-':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Right.png")), (32, 32)), False, True)
        elif wall_type == '=':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton.png")), (32, 32))
        elif wall_type == '[':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton - Left.png")), (32, 32))
        elif wall_type == ']':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton - Right.png")), (32, 32))
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Right.png")), (32, 32))
        
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class DoorSprite(pygame.sprite.Sprite):

    direction: int

    def __init__(self, pos_x, pos_y, direction, door_type):

        super().__init__()

        if door_type == '0':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door.png")), (32, 32))
        elif door_type == '1':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Botton.png")), (32, 40))
        elif door_type == '2':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Lateral.png")), (32, 32)), True, False)
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Lateral.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self.direction = direction

class DecorationSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y):

        super().__init__()

        flip = False

        if randint(0, 1) == 0:

            flip = True

        self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Decoration", "Skull.png")), (32, 32)), flip, False)
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y

class EntityBaseSprite(pygame.sprite.Sprite):

    entity_sprites: pygame.sprite.RenderPlain()
    item_sprite: pygame.sprite.Sprite
    render_area: pygame.sprite.Sprite
    _old_attacking_state: bool

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.Surface([32, 32])
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self.entity_sprites = pygame.sprite.RenderPlain()
        self.render_area = RenderAreaSprite(self.rect.centerx, self.rect.centery, 48, 48)
        self._old_attacking_state = False
    
    def update(self, pos_x, pos_y, horizontal_orientation, attacking):

        self.rect.x = pos_x
        self.rect.y = pos_y

        if attacking != self._old_attacking_state:

            if attacking:

                self.entity_sprites.add(self.item_sprite)
            else:

                self.entity_sprites.remove(self.item_sprite)

        self._old_attacking_state = attacking

        self.entity_sprites.update(pos_x, pos_y, horizontal_orientation)
        self.item_sprite.update(pos_x, pos_y, horizontal_orientation)
        self.render_area.update(self.rect.centerx, self.rect.centery)

class EntitySprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int
    walking_freq: float
    walking_amp: float

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self._old_horizontal_orientation = 1
        self.walking_freq = 1.0
        self.walking_amp = 1.0
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        if abs(self.rect.x - pos_x) < 1.0:

            self.rect.y = pos_y + self.walking_amp * sin(pos_y * self.walking_freq)
        else:

            self.rect.y = pos_y + self.walking_amp * sin(pos_x * self.walking_freq)

        self.rect.x = pos_x

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation

class RenderAreaSprite(pygame.sprite.Sprite):

    def __init__(self, pos_x, pos_y, width, height):

        super().__init__()
        self.image = pygame.Surface([width, height])
        self.rect = self.image.get_rect()
        self.rect.centerx = pos_x
        self.rect.centery = pos_y
    
    def update(self, pos_x, pos_y):

        self.rect.centerx = pos_x
        self.rect.centery = pos_y

class PlayerBaseSprite(EntityBaseSprite):

    def __init__(self, pos_x, pos_y):

        super().__init__(pos_x, pos_y)

        self.entity_sprites.add(PlayerSprite(pos_x, pos_y))
        self.render_area = RenderAreaSprite(self.rect.centerx, self.rect.centery, 56, 56)
        self.item_sprite = SwordSprite(pos_x, pos_y)

class MonsterBaseSprite(EntityBaseSprite):

    def __init__(self, pos_x, pos_y):

        super().__init__(pos_x, pos_y)

        self.entity_sprites.add(MonsterSprite(pos_x, pos_y))
        self.item_sprite = SwordSprite(pos_x, pos_y)

class PlayerSprite(EntitySprite):

    def __init__(self, pos_x, pos_y):

        super().__init__(pos_x, pos_y)
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_{0}.png".format(randint(0, 13)))), (32, 32))
        self.walking_freq = 0.3
        self.walking_amp = 2.0

class MonsterSprite(EntitySprite):

    def __init__(self, pos_x, pos_y):

        super().__init__(pos_x, pos_y)
        self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Monsters", "Monster_{0}.png".format(randint(0, 24)))), (32, 32)), True, False)
        self.walking_freq = 0.5
        self.walking_amp = 2.0

class SwordSprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int

    def __init__(self, pos_x, pos_y):

        super().__init__()

        self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Itens", "Sword.png")), (14, 28)), -90)
        self.rect = self.image.get_rect()
        self.rect.x = pos_x + 14
        self.rect.y = pos_y + 16
        self._old_horizontal_orientation = 1
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        if self._old_horizontal_orientation == 1:

            self.rect.x = pos_x + 14
        else:

            self.rect.x = pos_x - 14
        self.rect.y = pos_y + 16

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            self._old_horizontal_orientation = horizontal_orientation