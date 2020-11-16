# -*- coding: utf-8 -*-

import pygame
import Graphics

class Entity():

    position = [0, 0]
    speed = 1.0

    sprites: pygame.sprite.RenderPlain()

    def __init__(self, position):

        self.position = position
        self.sprites = pygame.sprite.RenderPlain()

class Player(Entity):

    def __init__(self, position):

        super().__init__(position)

        self.speed = 5.0
        self.sprites.add(Graphics.PlayerSprite(self.position[0], self.position[1]))
    
    def Move(self, x, y):

        self.position[0] += x
        self.position[1] += y
        self.sprites.update(self.position[0], self.position[1])