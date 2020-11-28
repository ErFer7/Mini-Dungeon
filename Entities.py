# -*- coding: utf-8 -*-

import os

from enum import Enum
from math import sqrt
from random import randint

import pygame
import graphics

class EntityState(Enum):

    IDLING = 1
    ATTACKING = 2
    STUNNED = 3
    DEAD = 4

class Entity():

    position: list
    direction: list
    velocity: list
    drag: float
    speed: float
    life: int
    _power: float
    _attack_time: float
    _attack_time_counter: int
    _stun_time: float
    _stun_time_counter: int
    _state: EntityState
    sprites: pygame.sprite.RenderPlain
    attack_sound: pygame.mixer.Sound
    collision_sound: pygame.mixer.Sound

    def __init__(self, position):

        self.position = position[:]
        self.direction = [0, 0]
        self.velocity = [0.0, 0.0]
        self.drag = 0.25
        self.speed = 1.0
        self.life = 100.0
        self.power = 1.0
        self._attack_time = 0.1
        self._attack_time_counter = 0
        self._stun_time = 0.5
        self._stun_time_counter = 0
        self._state = EntityState.IDLING
        self.sprites = pygame.sprite.RenderPlain()
        self.collision_sound = pygame.mixer.Sound(os.path.join("Audio", "Collision.wav"))
    
    def attack(self):

        self._state = EntityState.ATTACKING

    def change_life(self, value):

        self.life += value

        if value < 0:

            self._state = EntityState.STUNNED

        if self.life <= 0.0:

            self.life = 0.0
            self._state = EntityState.DEAD
        elif self.life > 100.0:

            self.life = 100.0
    
    def is_attacking(self):

        if self._state == EntityState.ATTACKING:

            return True
        else:

            return False
    
    def is_dead(self):

        if self._state == EntityState.DEAD:

            return True
        else:

            return False

    def delete(self):

        if len(self.sprites.sprites()) > 0:

            self.sprites.sprites()[0].entity_sprites.empty()
        self.sprites.empty()

class Player(Entity):

    kill_count: int
    game_over_sound: pygame.mixer.Sound
    kill_sound: pygame.mixer.Sound

    def __init__(self, position):

        super().__init__(position)

        self.speed = 2.0
        self._stun_time = 0.1
        self.power = 3.5
        self.kill_count = 0
        self.attack_sound = pygame.mixer.Sound(os.path.join("Audio", "Sword attack.wav"))
        self.game_over_sound = pygame.mixer.Sound(os.path.join("Audio", "Game over.wav"))
        self.kill_sound = pygame.mixer.Sound(os.path.join("Audio", "Kill.wav"))
        self.sprites.add(graphics.PlayerBaseSprite((self.position[0] - 16, self.position[1] - 16)))
    
    def update(self, event):

        if event is not None and self._state != EntityState.STUNNED:

            if event.type == pygame.KEYDOWN:
                    
                if event.key == pygame.K_LEFT:

                    self.direction[0] = -1
                    self.velocity[0] = -self.speed
                elif event.key == pygame.K_RIGHT:

                    self.direction[0] = 1
                    self.velocity[0] = self.speed
                    
                if event.key == pygame.K_DOWN:

                    self.direction[1] = 1
                    self.velocity[1] = self.speed
                elif event.key == pygame.K_UP:

                    self.direction[1] = -1
                    self.velocity[1] = -self.speed
                
            if event.type == pygame.KEYUP:

                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:

                    self.direction[0] = 0
                    
                if event.key == pygame.K_DOWN or event.key == pygame.K_UP:

                    self.direction[1] = 0
            
            if event.type == pygame.KEYDOWN and event.key == pygame.K_x and not self.is_attacking():

                self.attack()
        elif self._state == EntityState.STUNNED:

            self.direction[0] = 0
            self.direction[1] = 0
        
        if self._state == EntityState.ATTACKING:

            self._attack_time_counter += 1

            if self._attack_time_counter > 60 * self._attack_time:

                self._attack_time_counter = 0
                self._state = EntityState.IDLING
        elif self._state == EntityState.STUNNED:

            self._stun_time_counter += 1

            if self._stun_time_counter > 60 * self._stun_time:

                self._stun_time_counter = 0
                self._state = EntityState.IDLING

class Monster(Entity):
    
    _sight_distance: float

    def __init__(self, position):

        super().__init__(position)

        self.power = 4.5
        self.speed = 1.0
        self._stun_time = 0.1
        self._sight_distance = 400.0
        self.attack_sound = pygame.mixer.Sound(os.path.join("Audio", "Monster attack.wav"))
        self.sprites.add(graphics.MonsterBaseSprite((self.position[0] - 16, self.position[1] - 16)))
    
    def update(self, player_position, obstacles):
        
        distance_from_player = sqrt((player_position[0] - self.position[0]) ** 2 + (player_position[1] - self.position[1]) ** 2)

        if distance_from_player <= self._sight_distance and self._state != EntityState.DEAD and self._state != EntityState.STUNNED:

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

                if distance_from_player <= 16 and not self.is_attacking():

                    self.attack()
        else:

            self.direction[0] = 0
            self.direction[1] = 0
        
        if self._state == EntityState.ATTACKING:

            self._attack_time_counter += 1

            if self._attack_time_counter > int(60 * self._attack_time):

                self._attack_time_counter = 0
                self._state = EntityState.IDLING
        elif self._state == EntityState.STUNNED:

            self._stun_time_counter += 1

            if self._stun_time_counter > 60 * self._stun_time:

                self._stun_time_counter = 0
                self._state = EntityState.IDLING
    
    def drop(self, entities, key):

        if randint(0, 3) == 0:

            drop_key = key + "_drop"
            entities[drop_key] = HealthPotion(self.position)

class HealthPotion(Entity):

    heal_sound: pygame.mixer.Sound

    def __init__(self, position):

        super().__init__(position)

        self.heal_sound = pygame.mixer.Sound(os.path.join("Audio", "Heal.wav"))
        self.sprites.add(graphics.HealthPotionBaseSprite((self.position[0] - 16, self.position[1] - 16)))