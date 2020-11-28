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
    monster_ammount: int
    collision_sprites: pygame.sprite.RenderPlain
    trigger_sprites: pygame.sprite.RenderPlain
    sprites: pygame.sprite.RenderPlain

    def __init__(self, doors, file, screen_size, difficulty, initial_monster_ammount):

        self.doors = doors[:]
        self.doors_leaving_position = [[], [], [], []]
        self.player_spawn_position = []
        self.entities = {}
        self.monster_ammount = 0
        self.collision_sprites = pygame.sprite.RenderPlain()
        self.trigger_sprites = pygame.sprite.RenderPlain()
        self.sprites = pygame.sprite.RenderPlain()

        position = [0, 0]

        stage = 0
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

                    position[0] = (screen_size[0] - room_size[0] * 32) / 2
                    position[1] = (screen_size[1] - room_size[1] * 32) / 2
                else:
                    
                    if stage == 2:

                        for char in line:

                            if char in '#;':

                                if char == '#':

                                    self.collision_sprites.add(graphics.WallSprite(position, char))
                                else:

                                    self.collision_sprites.add(graphics.BoxSprite(position))
                            elif char in "0123":

                                if self.doors[int(char)]:

                                    self.trigger_sprites.add(graphics.DoorSprite(position, int(char), char))
                                else:

                                    if char == '0':

                                        self.collision_sprites.add(graphics.WallSprite(position, '#'))
                                    elif char == '2':

                                        self.collision_sprites.add(graphics.WallSprite(position, '%'))
                                    elif char == '3':

                                        self.collision_sprites.add(graphics.WallSprite(position, '$'))
                                    else:

                                        self.collision_sprites.add(graphics.WallSprite(position, '='))
                            elif char in "@_&":

                                self.sprites.add(graphics.WallSprite(position, char))
                            elif char in "[].":

                                if char != '.':

                                    self.sprites.add(graphics.WallSprite((position[0], position[1] - 24), char))
                                else:

                                    self.sprites.add(graphics.WallSprite((position[0], position[1] - 24), '#'))
                            elif char in "$%+-=":

                                self.collision_sprites.add(graphics.WallSprite(position, char))
                            elif char in "qwer^v<>tyui'":
                                
                                self.sprites.add(graphics.FloorSprite(position, char))

                                if randint(0, 110) == 110:

                                    self.sprites.add(graphics.DecorationSprite(position))

                            position[0] += 32
                        
                        position[0] = (screen_size[0] - room_size[0] * 32) / 2
                        position[1] += 32
                    elif stage == 3:

                        for char in line:

                            if char == 'P':

                                self.player_spawn_position = [position[0] + 16, position[1] + 16]
                            elif char in "0123":

                                if self.doors[int(char)]:
                                    
                                    self.doors_leaving_position[int(char)] = [position[0] + 16, position[1] + 16]
                            elif char == 'M':

                                if randint(0, 10) <= difficulty or initial_monster_ammount == 0:

                                    self.entities["Monster_{0}".format(self.monster_ammount)] = entities.Monster([position[0] + 16, position[1] + 16])
                                    self.monster_ammount += 1
                            
                            position[0] += 32
                        
                        position[0] = (screen_size[0] - room_size[0] * 32) / 2
                        position[1] += 32
    
    def delete(self):

        for key in self.entities:

            self.entities[key].delete()
        
        self.collision_sprites.empty()
        self.trigger_sprites.empty()
        self.sprites.empty()
                
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
    initial_monster_ammount = 0

    player_col = randint(0, width - 1)
    player_ln = randint(0, heigth - 1)

    for i in range(heigth):

        rooms.append([])
        for j in range(width):

            room = Room(structure[i][j], choice(os.listdir("Rooms")), screen_size, abs(i - player_ln) + abs(j - player_col), initial_monster_ammount)
            initial_monster_ammount += room.monster_ammount

            rooms[i].append(room)

    player = entities.Player(rooms[player_ln][player_col].player_spawn_position)

    rooms[player_ln][player_col].entities["Player"] = player
    
    return player, rooms, [player_ln, player_col], initial_monster_ammount
