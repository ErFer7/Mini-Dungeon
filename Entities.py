# -*- coding: utf-8 -*-

from enum import Enum

import pygame
import graphics

from math import sqrt

class EntityState(Enum):

    IDLE = 1
    ATTACK = 2
    DEAD = 3

class Entity():

    position: list
    direction: list
    velocity: list
    drag: float
    speed: float
    life: int
    power: float
    state: EntityState
    sprites: pygame.sprite.RenderPlain()

    def __init__(self, position):

        self.position = position
        self.direction = [0, 0]
        self.velocity = [0.0, 0.0]
        self.drag = 0.25
        self.speed = 1.0
        self.life = 100
        self.power = 1.0
        self.state = EntityState.IDLE
        self.sprites = pygame.sprite.RenderPlain()
    
    def attack(self, target = None):

        self.state = EntityState.ATTACK
        
        if target != None:

            target.change_life(-self.power)

    def change_life(self, value):

        self.life += value

        if self.life <= 0:

            self.state = EntityState.DEAD

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
            
            if event.type == pygame.MOUSEBUTTONDOWN:

                self.attack()

class Monster(Entity):
    
    sight_distance: float

    def __init__(self, position):

        super().__init__(position)

        self.sight_distance = 256.0
        self.sprites.add(graphics.MonsterSprite(self.position[0], self.position[1]))
    
    def behaviour(self, player_position):

        if sqrt((player_position[0] - self.position[0]) ** 2 + (player_position[1] - self.position[1]) ** 2) <= self.sight_distance:

            if abs(player_position[0] - self.position[0]) > 3.0:

                if self.position[0] < player_position[0]:

                    self.direction[0] = 1   
                    self.velocity[0] = self.speed
                elif self.position[0] > player_position[0]:

                    self.direction[0] = -1
                    self.velocity[0] = -self.speed
            else:

                self.direction[0] = 0

            if abs(player_position[1] - self.position[1]) > 3.0:

                if self.position[1] < player_position[1]:

                    self.direction[1] = 1
                    self.velocity[1] = self.speed
                elif self.position[1] > player_position[1]:

                    self.direction[1] = -1
                    self.velocity[1] = -self.speed
            else:

                self.direction[1] = 0
        else:

            self.direction[0] = 0
            self.direction[1] = 0