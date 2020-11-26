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
        self.sprites.add(graphics.PlayerBaseSprite(self.position[0] - 16, self.position[1] - 16))
    
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

        self.sight_distance = 300.0
        self.sprites.add(graphics.MonsterBaseSprite(self.position[0] - 16, self.position[1] - 16))
    
    def behaviour(self, player_position, obstacles):
        
        distance_from_player = sqrt((player_position[0] - self.position[0]) ** 2 + (player_position[1] - self.position[1]) ** 2)

        if distance_from_player <= self.sight_distance and distance_from_player >= 40:

            has_line_of_sight = True

            ang_coeff = 0.0

            is_vertical = False
            is_horizontal = False

            if (player_position[0] - self.position[0]) == 0.0:

                is_vertical = True
            elif (self.position[1] - player_position[1]) == 0.0:

                is_horizontal = True
            else:

                ang_coeff = (self.position[1] - player_position[1]) / (player_position[0] - self.position[0])

            for obstacle in obstacles:
                
                obstacle_is_in_range_X = True
                obstacle_is_in_range_Y = True

                if player_position[0] >= self.position[0]:

                    if obstacle.rect.right <= self.position[0] or obstacle.rect.left >= player_position[0]:

                        obstacle_is_in_range_X = False
                else:

                    if obstacle.rect.left >= self.position[0] or obstacle.rect.right <= player_position[0]:

                        obstacle_is_in_range_X = False

                if -player_position[1] >= -self.position[1]:

                    if -obstacle.rect.top <= -self.position[1] or -obstacle.rect.bottom >= -player_position[1]:

                        obstacle_is_in_range_Y = False
                else:

                    if -obstacle.rect.bottom >= -self.position[1] or -obstacle.rect.top <= -player_position[1]:

                        obstacle_is_in_range_Y = False

                if obstacle_is_in_range_X and obstacle_is_in_range_Y:

                    top_left = (obstacle.rect.topleft[0] - self.position[0], self.position[1] - obstacle.rect.topleft[1])
                    top_right = (obstacle.rect.topright[0] - self.position[0], self.position[1] - obstacle.rect.topright[1])
                    botton_right = (obstacle.rect.bottomright[0] - self.position[0], self.position[1] - obstacle.rect.bottomright[1])
                    botton_left = (obstacle.rect.bottomleft[0] - self.position[0], self.position[1] - obstacle.rect.bottomleft[1])

                    if is_horizontal:
                        
                        if top_left[1] == 0:

                            has_line_of_sight = False
                            break

                        if botton_left[1] == 0:

                            has_line_of_sight = False
                            break

                        if botton_left[1] <= 0 and top_left[1] >= 0:

                            has_line_of_sight = False
                            break

                        if botton_right[1] <= 0 and top_right[1] >= 0:

                            has_line_of_sight = False
                            break
                    elif is_vertical:
                    
                        if top_left[0] <= 0 and top_right[0] >= 0:
                            
                            has_line_of_sight = False
                            break

                        if botton_left[0] <= 0 and botton_right[0] >= 0:
                            
                            has_line_of_sight = False
                            break

                        if botton_left[0] == 0:

                            has_line_of_sight = False
                            break

                        if botton_right[0] == 0:

                            has_line_of_sight = False
                            break
                    else:

                        if top_left[1] / ang_coeff >= top_left[0] and top_right[1] / ang_coeff <= top_right[0]:
                            
                            has_line_of_sight = False
                            break

                        if botton_left[1] / ang_coeff >= botton_left[0] and botton_right[1] / ang_coeff <= botton_right[0]:

                            has_line_of_sight = False
                            break

                        if botton_left[0] * ang_coeff >= botton_left[1] and top_left[0] * ang_coeff <= top_left[1]:

                            has_line_of_sight = False
                            break

                        if botton_right[0] * ang_coeff >= botton_right[1] and top_right[0] * ang_coeff <= top_right[1]:

                            has_line_of_sight = False
                            break

            if has_line_of_sight:

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