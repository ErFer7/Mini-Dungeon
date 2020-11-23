# -*- coding: utf-8 -*-

import os
import pygame
import graphics
import entities

from random import randint, choice
from enum import Enum

class Direction(Enum):

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

class Room():
    
    doors: list
    doors_leaving_position:list
    player_spawn_position: list
    entities: dict
    collision_sprites: pygame.sprite.RenderPlain()
    trigger_sprites: pygame.sprite.RenderPlain()
    sprites: pygame.sprite.RenderPlain()

    def __init__(self, doors, file, screen_size):

        self.doors = doors[:]
        self.doors_leaving_position = [[], [], [], []]
        self.player_spawn_position = []
        self.entities = {}
        self.collision_sprites = pygame.sprite.RenderPlain()
        self.trigger_sprites = pygame.sprite.RenderPlain()
        self.sprites = pygame.sprite.RenderPlain()

        position = [0, 0]

        stage = 0
        monster_count = 0
        room_size = []

        with open(os.path.join("Rooms", file), 'r', encoding = "utf-8") as room_file:
            
            room_txt = room_file.readlines()

        for line in room_txt:

            if not line.startswith('/'):

                if line.startswith('!'):

                    stage += 1
                    
                    if stage == 1:
                        
                        line_list = line.split()
                        room_size = [int(line_list[2]), int(line_list[3])]

                    position[0] = (screen_size[1] - room_size[1] * 32) / 2
                    position[1] = (screen_size[0] - room_size[0] * 32) / 2
                else:
                    
                    if stage == 2:

                        for char in line:

                            if char == '#':

                                self.collision_sprites.add(graphics.WallSprite(position[1], position[0], char))
                            elif char in "0123":

                                if self.doors[int(char)]:

                                    self.doors_leaving_position
                                    self.trigger_sprites.add(graphics.DoorSprite(position[1], position[0], int(char)))
                                else:

                                    if char == '0':

                                        self.collision_sprites.add(graphics.WallSprite(position[1], position[0], '#'))
                                    elif char == '2':

                                        self.collision_sprites.add(graphics.WallSprite(position[1], position[0], '%'))
                                    elif char == '3':

                                        self.collision_sprites.add(graphics.WallSprite(position[1], position[0], '$'))
                                    else:

                                        self.collision_sprites.add(graphics.WallSprite(position[1], position[0], '='))
                            elif char in "@_&":

                                self.sprites.add(graphics.WallSprite(position[1], position[0], char))
                            elif char in "[].":

                                if char != '.':

                                    self.sprites.add(graphics.WallSprite(position[1], position[0] - 24, char))
                                else:

                                    self.sprites.add(graphics.WallSprite(position[1], position[0] - 24, '#'))
                            elif char in "$%+-=":

                                self.collision_sprites.add(graphics.WallSprite(position[1], position[0], char))
                            elif char != "\n":
                                
                                self.sprites.add(graphics.FloorSprite(position[1], position[0], char))
                            
                            position[1] += 32
                        
                        position[0] += 32
                        position[1] = (screen_size[0] - room_size[0] * 32) / 2
                    elif stage == 3:

                        for char in line:

                            if char == 'P':

                                self.player_spawn_position = [position[1], position[0]]
                            elif char in "0123":

                                if self.doors[int(char)]:
                                    
                                    self.doors_leaving_position[int(char)] = [position[1], position[0]]
                            elif char == 'M':

                                self.entities["Monster_{0}".format(monster_count)] = entities.Monster([position[1], position[0]])
                                monster_count += 1
                            
                            position[1] += 32
                        
                        position[0] += 32
                        position[1] = (screen_size[0] - room_size[0] * 32) / 2
                
def generate_dungeon(screen_size, width = 1, heigth = 1):

    # Cima, Baixo, Direita e Esquerda
    structure = []
    
    for i in range(heigth):

        structure.append([])
        for _ in range(width):

            structure[i].append([False] * 4)

    room_struct_list = []
    rooms_struct_stack = []

    position = [randint(0, width - 1), randint(0, heigth - 1)]

    back_tracking = False

    while True:

        directions = []

        if not back_tracking:

            room_struct_list.append(position[:])
            rooms_struct_stack.append(position[:])

        if len(room_struct_list) >= width * heigth:

            break

        if position[1] > 0 and ([position[0], position[1] - 1] not in room_struct_list) and not (structure[position[1]][position[0]][0] or structure[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        if position[1] < heigth - 1 and ([position[0], position[1] + 1] not in room_struct_list) and not (structure[position[1]][position[0]][1] or structure[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        if position[0] < width - 1 and ([position[0] + 1, position[1]] not in room_struct_list) and not (structure[position[1]][position[0]][2] or structure[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        if position[0] > 0 and ([position[0] - 1, position[1]] not in room_struct_list) and not (structure[position[1]][position[0]][3] or structure[position[1]][position[0] - 1][2]):

            directions.append(Direction.LEFT)

        if len(directions) == 0:

            back_tracking = True
            rooms_struct_stack.remove(rooms_struct_stack[-1])
            position = rooms_struct_stack[-1]
        else:

            back_tracking = False
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

            rooms[i].append(Room(structure[i][j], choice(os.listdir("Rooms")), screen_size))
    
    player_x = randint(0, width - 1)
    player_y = randint(0, heigth - 1)

    player = entities.Player(rooms[player_x][player_y].player_spawn_position)

    rooms[player_x][player_y].entities["Player"] = player
    
    return player, rooms, [player_x, player_y]