# -*- coding: utf-8 -*-

import os
import pygame
import GraphicsManager

from random import randint, choice
from enum import Enum

class Direction(Enum):

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

class Room():
    
    doors = []
    sprites = pygame.sprite.RenderPlain()

    def __init__(self, doors, file):

        self.doors = doors

        position = [0, 0]

        readingBase = False
        readingEntities = False

        with open(file, "r", encoding = "utf-8") as roomFile:
            
            roomTxt = roomFile.readlines()

        for line in roomTxt:

            if not line.startswith("/"):

                if line.startswith("!"):

                    if not readingBase:

                        readingBase = True
                        readingEntities = False
                    elif not readingEntities:

                        readingBase = False
                        readingEntities = True
                else:

                    if readingBase:

                        for char in line:

                            if char == "#":

                                self.sprites.add(GraphicsManager.WallSprite(position[1], position[0]))
                            elif char == "_":

                                self.sprites.add(GraphicsManager.DoorSprite(position[1], position[0]))
                            elif char != "\n":
                                
                                self.sprites.add(GraphicsManager.FloorSprite(position[1], position[0], char))
                            
                            position[1] += 64
                        
                        position[0] += 64
                        position[1] = 0
                    
                    # ENTITIES serão ignoradas por enquanto
                
def GenerateDungeon(width = 2, heigth = 2):

    # Cima, Baixo, Direita e Esquerda
    roomsMat = []
    
    for i in range(heigth):

        roomsMat.append([])
        for _ in range(width):

            roomsMat[i].append([False] * 4)

    roomsList = []
    roomsStack = []

    position = [randint(0, width - 1), randint(0, heigth - 1)]

    backTracking = False

    while True:

        directions = []

        if not backTracking:

            roomsList.append(position[:])
            roomsStack.append(position[:])

        if len(roomsList) >= width * heigth:

            roomsList.clear()
            roomsStack.clear()

            break

        if position[1] > 0 and ([position[0], position[1] - 1] not in roomsList) and not (roomsMat[position[1]][position[0]][0] or roomsMat[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        if position[1] < heigth - 1 and ([position[0], position[1] + 1] not in roomsList) and not (roomsMat[position[1]][position[0]][1] or roomsMat[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        if position[0] < width - 1 and ([position[0] + 1, position[1]] not in roomsList) and not (roomsMat[position[1]][position[0]][2] or roomsMat[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        if position[0] > 0 and ([position[0] - 1, position[1]] not in roomsList) and not (roomsMat[position[1]][position[0]][3] or roomsMat[position[1]][position[0] - 1][2]):

            directions.append(Direction.LEFT)

        if len(directions) == 0:

            backTracking = True
            roomsStack.remove(roomsStack[-1])
            position = roomsStack[-1]
        else:

            backTracking = False
            direction = choice(directions)

            if direction == Direction.UP:

                roomsMat[position[1]][position[0]][0] = True
                roomsMat[position[1] - 1][position[0]][1] = True

                position[1] -= 1
            elif direction == Direction.DOWN:

                roomsMat[position[1]][position[0]][1] = True
                roomsMat[position[1] + 1][position[0]][0] = True

                position[1] += 1
            elif direction == Direction.RIGHT:

                roomsMat[position[1]][position[0]][2] = True
                roomsMat[position[1]][position[0] + 1][3] = True

                position[0] += 1
            else:

                roomsMat[position[1]][position[0]][3] = True
                roomsMat[position[1]][position[0] - 1][2] = True

                position[0] -= 1
    
    rooms = []

    for i in range(heigth):

        rooms.append([])
        for j in range(width):

            rooms[i].append(Room(roomsMat[i][j], os.path.join("Rooms", "Test.room")))

    return rooms