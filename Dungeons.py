# -*- coding: utf-8 -*-

import os
import pygame
import Graphics
import Entities

from random import randint, choice
from enum import Enum

class Direction(Enum):

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

class Room():
    
    doors = []
    playerSpawnPosition = []
    entities = []

    sprites: pygame.sprite.RenderPlain()

    def __init__(self, doors, file, screenSize):

        self.doors = doors[:]
        self.sprites = pygame.sprite.RenderPlain()

        _position = [0, 0]

        _stage = 0
        _doorsChars = "0123"

        with open(file, 'r', encoding = "utf-8") as roomFile:
            
            roomTxt = roomFile.readlines()

        for line in roomTxt:

            if not line.startswith('/'):

                if line.startswith('!'):

                    _stage += 1
                else:
                    
                    if _stage == 1:

                        w, h = map(int, line.split())

                        _position[0] = (screenSize[1] - h * 48) / 2
                        _position[1] = (screenSize[0] - w * 48) / 2
                    elif _stage == 2:

                        for char in line:

                            if char == '#':

                                self.sprites.add(Graphics.WallSprite(_position[1], _position[0]))
                            elif char in _doorsChars:

                                if self.doors[int(char)]:

                                    self.sprites.add(Graphics.DoorSprite(_position[1], _position[0]))
                                else:

                                    self.sprites.add(Graphics.WallSprite(_position[1], _position[0]))
                            elif char != "\n":
                                
                                self.sprites.add(Graphics.FloorSprite(_position[1], _position[0], char))
                            
                            _position[1] += 48
                        
                        _position[0] += 48
                        _position[1] = (screenSize[0] - w * 48) / 2
                    else:

                        if line.startswith("Player"):

                            self.playerSpawnPosition = [int(line.split()[1]) * 48, int(line.split()[2]) * 48]
                
def GenerateDungeon(screenSize, width = 2, heigth = 2):

    # Cima, Baixo, Direita e Esquerda
    structure = []
    
    for i in range(heigth):

        structure.append([])
        for _ in range(width):

            structure[i].append([False] * 4)

    roomStructList = []
    roomsStructStack = []

    position = [randint(0, width - 1), randint(0, heigth - 1)]

    backTracking = False

    while True:

        directions = []

        if not backTracking:

            roomStructList.append(position[:])
            roomsStructStack.append(position[:])

        if len(roomStructList) >= width * heigth:

            roomStructList.clear()
            roomsStructStack.clear()

            break

        if position[1] > 0 and ([position[0], position[1] - 1] not in roomStructList) and not (structure[position[1]][position[0]][0] or structure[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        if position[1] < heigth - 1 and ([position[0], position[1] + 1] not in roomStructList) and not (structure[position[1]][position[0]][1] or structure[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        if position[0] < width - 1 and ([position[0] + 1, position[1]] not in roomStructList) and not (structure[position[1]][position[0]][2] or structure[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        if position[0] > 0 and ([position[0] - 1, position[1]] not in roomStructList) and not (structure[position[1]][position[0]][3] or structure[position[1]][position[0] - 1][2]):

            directions.append(Direction.LEFT)

        if len(directions) == 0:

            backTracking = True
            roomsStructStack.remove(roomsStructStack[-1])
            position = roomsStructStack[-1]
        else:

            backTracking = False
            direction = choice(directions)

            if direction == Direction.UP:

                structure[position[1]][position[0]][0] = True
                structure[position[1] - 1][position[0]][1] = True

                position[1] -= 1
            elif direction == Direction.DOWN:

                structure[position[1]][position[0]][1] = True
                structure[position[1] + 1][position[0]][0] = True

                position[1] += 1
            elif direction == Direction.RIGHT:

                structure[position[1]][position[0]][2] = True
                structure[position[1]][position[0] + 1][3] = True

                position[0] += 1
            else:

                structure[position[1]][position[0]][3] = True
                structure[position[1]][position[0] - 1][2] = True

                position[0] -= 1
    
    rooms = []

    for i in range(heigth):

        rooms.append([])
        for j in range(width):

            rooms[i].append(Room(structure[i][j], os.path.join("Rooms", "Test.room"), screenSize))
    
    playerX = randint(0, width - 1)
    playerY = randint(0, heigth - 1)

    rooms[playerX][playerY].entities.append(Entities.Player(rooms[playerX][playerY].playerSpawnPosition))
    
    return rooms, [playerX, playerY]