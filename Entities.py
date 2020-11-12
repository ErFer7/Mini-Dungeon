# -*- coding: utf-8 -*-

import pygame
import GraphicsManager

class Entity():

    position = [0, 0]

    speed = 1.0
    # health = 100
    # mana = 0
    # armor = 0
    # force = 0
    # dexterity = 0
    # inteligence = 0

    # inventory = []
    # armorInventory = []
    # hands = []

class Player(Entity):

    sprites = pygame.sprite.RenderPlain()

    def __init__(self, posX, posY):

        super().__init__()

        self.position[0] = posX
        self.position[1] = posY
        self.speed = 5.0
        self.sprites.add(GraphicsManager.PlayerSprite(posX, posY))
    
    def Move(self, x, y):

        self.position[0] += x
        self.position[1] += y
        self.sprites.update(self.position[0], self.position[1])