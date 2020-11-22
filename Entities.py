# -*- coding: utf-8 -*-

import pygame
import graphics

class Entity():

    position: list
    direction: list
    velocity: list
    drag: float
    speed: float
    sprites: pygame.sprite.RenderPlain()

    def __init__(self, position):

        self.position = position
        self.direction = [0, 0]
        self.velocity = [0.0, 0.0]
        self.drag = 0.25
        self.speed = 1.0
        self.sprites = pygame.sprite.RenderPlain()

class Player(Entity):

    def __init__(self, position):

        super().__init__(position)

        self.speed = 2.0
        self.sprites.add(graphics.PlayerSprite(self.position[0], self.position[1]))
    
    def control(self, event):

        if event != None:

            if event.type == pygame.KEYDOWN:
                    
                if event.key == pygame.K_a:

                    self.direction[0] = -1
                    self.velocity[0] = -self.speed
                elif event.key == pygame.K_d:

                    self.direction[0] = 1
                    self.velocity[0] = self.speed
                    
                if event.key == pygame.K_s:

                    self.direction[1] = 1
                    self.velocity[1] = self.speed
                elif event.key == pygame.K_w:

                    self.direction[1] = -1
                    self.velocity[1] = -self.speed
                
            if event.type == pygame.KEYUP:

                if event.key == pygame.K_a or event.key == pygame.K_d:

                    self.direction[0] = 0
                    
                if event.key == pygame.K_s or event.key == pygame.K_w:

                    self.direction[1] = 0

class Monster(Entity):
    
    def __init__(self, position):

        super().__init__(position)

        self.speed = 2.0
        self.sprites.add(graphics.MonsterSprite(self.position[0], self.position[1]))
    
    #def behaviour(self, player_position):

        