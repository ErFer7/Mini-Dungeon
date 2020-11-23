# -*- coding: utf-8 -*-

import os
import pygame

class RenderControl():

    update_all: bool

    def __init__(self, update_all_init):

        self.update_all = update_all_init

    def update_graphics(self, room, display):

        if self.update_all:

            display.fill((10, 10, 10))

            room.sprites.draw(display)
            room.collision_sprites.draw(display)
            room.trigger_sprites.draw(display)
            
            self.update_all = False
        else:

            for key in room.entities:

                background_groups = [room.collision_sprites, room.trigger_sprites, room.sprites]
                overlap_group = pygame.sprite.RenderPlain()

                for group in background_groups:
                    
                    overlap = pygame.sprite.spritecollide(room.entities[key].sprites.sprites()[0].render_area, group, False)

                    if overlap != None:

                        for sprite in overlap:

                            overlap_group.add(sprite)

                overlap_group.draw(display)
        
            for key in room.entities:

                room.entities[key].sprites.draw(display)

        pygame.display.update()

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

class PlayerSprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int
    render_area: pygame.sprite.Sprite

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_15.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self._old_horizontal_orientation = 1
        self.render_area = RenderAreaSprite(self.rect.centerx, self.rect.centery, 48, 48)
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        self.rect.x = pos_x
        self.rect.y = pos_y

        self.render_area.update(self.rect.centerx, self.rect.centery)

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation

class MonsterSprite(pygame.sprite.Sprite):

    _old_horizontal_orientation: int
    render_area: pygame.sprite.Sprite

    def __init__(self, pos_x, pos_y):

        super().__init__()
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = pos_x
        self.rect.y = pos_y
        self._old_horizontal_orientation = 1
        self.render_area = RenderAreaSprite(self.rect.centerx, self.rect.centery, 48, 48)
    
    def update(self, pos_x, pos_y, horizontal_orientation):

        self.rect.x = pos_x
        self.rect.y = pos_y

        self.render_area.update(self.rect.centerx, self.rect.centery)

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation