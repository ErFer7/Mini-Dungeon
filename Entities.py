# -*- coding: utf-8 -*-

import pygame
import Graphics

class Entity():

    position = [0, 0]
    direction = [0, 0]
    velocity = [0.0, 0.0]

    drag = 0.25
    speed = 1.0

    simulating = False

    sprites: pygame.sprite.RenderPlain()

    def __init__(self, position):

        self.position = position
        self.sprites = pygame.sprite.RenderPlain()

class Player(Entity):

    def __init__(self, position):

        super().__init__(position)

        self.speed = 2.5
        self.simulating = True
        self.sprites.add(Graphics.PlayerSprite(self.position[0], self.position[1]))
    
    def Control(self, event):

        # Otimizar no futuro
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