# -*- coding: utf-8 -*-

'''
Neste módulo estão definidos como as dungeons são geradas e seu funcionamento
'''

import os

from random import randint, choice
from enum import Enum

import pygame
import graphics
import entities

class Direction(Enum):
    
    '''
    Definições de direções
    '''

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

class Room():

    '''
    Definições de uma sala.

    A sala é lida de um arquivo em que cada caractere corresponde a um sprite
    '''

    doors: list # Definição as portas
    doors_leaving_position:list # Posições de saída das portas
    player_spawn_position: list # Posições de nascimento do jogador
    entities: dict # Dicionário que armazena as entidades
    monster_ammount: int # Número de monstros
    collision_sprites: pygame.sprite.RenderPlain # Sprites de colisão
    trigger_sprites: pygame.sprite.RenderPlain # Sprites das portas
    sprites: pygame.sprite.RenderPlain # Sprites gerais

    def __init__(self, doors, file, screen_size, difficulty, initial_monster_ammount):

        # Inicializa as variáveis
        self.doors = doors[:]
        self.doors_leaving_position = [[], [], [], []]
        self.player_spawn_position = []
        self.entities = {}
        self.monster_ammount = 0
        self.collision_sprites = pygame.sprite.RenderPlain()
        self.trigger_sprites = pygame.sprite.RenderPlain()
        self.sprites = pygame.sprite.RenderPlain()

        position = [0, 0] # Define a posição atual da leitura
        stage = 0 # Estágio da leitura
        room_size = [] # Definição do tamanho da sala

        # Abre o arquivo da sala
        with open(os.path.join("Rooms", file), 'r', encoding = "utf-8") as room_file:
            
            room_txt = room_file.readlines()

        for line in room_txt: # Para cada linha no arquivo

            if not line.startswith('/'): # Caso a linha não seja um "comentário"

                if line.startswith('!'): # Caso haja uma mudança de estado

                    stage += 1
                    
                    # Obtém o tamanho da sala
                    if stage == 1:
                        
                        line_list = line.split()
                        room_size = [int(line_list[2]), int(line_list[3])]

                    # Define as posições da leitura
                    position[0] = (screen_size[0] - room_size[0] * 32) / 2
                    position[1] = (screen_size[1] - room_size[1] * 32) / 2
                else:

                    if stage == 2: # Leitura da estrutura da sala

                        for char in line: # Para cada caractere na linha

                            if char in '#;': # Se o caractere é um obstáculo

                                if char == '#':

                                    # Parede normal
                                    self.collision_sprites.add(graphics.WallSprite(position, char))
                                else:

                                    # Caixa
                                    self.collision_sprites.add(graphics.BoxSprite(position))
                            elif char in "0123":

                                if self.doors[int(char)]: # Caso tenha uma porta nesta posição

                                    # Adiciona um sprite de porta
                                    self.trigger_sprites.add(graphics.DoorSprite(position, int(char), char))
                                else:

                                    if char == '0': # Parede normal

                                        self.collision_sprites.add(graphics.WallSprite(position, '#'))
                                    elif char == '2': # Parede da lateral direita

                                        self.collision_sprites.add(graphics.WallSprite(position, '%'))
                                    elif char == '3': # Parede da lateral esquerda

                                        self.collision_sprites.add(graphics.WallSprite(position, '$'))
                                    else: # Parede inferior

                                        self.collision_sprites.add(graphics.WallSprite(position, '='))
                            elif char in "@_&": # Topo da parede

                                self.sprites.add(graphics.WallSprite(position, char))
                            elif char in "[].": # Paredes de base

                                if char != '.': # Parede de base lateral

                                    self.sprites.add(graphics.WallSprite((position[0], position[1] - 24), char))
                                else: # Parede de base normal

                                    self.sprites.add(graphics.WallSprite((position[0], position[1] - 24), '#'))
                            elif char in "$%+-=": # Paredes laterais

                                self.collision_sprites.add(graphics.WallSprite(position, char))
                            elif char in "qwer^v<>tyui'": # Chão
                                
                                self.sprites.add(graphics.FloorSprite(position, char))

                                if randint(0, 110) == 110: # Há 1/110 de chance de gerar uma decoração (caveira)

                                    self.sprites.add(graphics.DecorationSprite(position))

                            position[0] += 32 # Incrementa a posição lateral
                        
                        # Ajusta as posições
                        position[0] = (screen_size[0] - room_size[0] * 32) / 2
                        position[1] += 32
                    elif stage == 3: # Leitura das entidades

                        for char in line: # Para cada caractere na linha

                            if char == 'P': # Jogador

                                self.player_spawn_position = [position[0] + 16, position[1] + 16]
                            elif char in "0123": # Saída da porta

                                if self.doors[int(char)]:
                                    
                                    self.doors_leaving_position[int(char)] = [position[0] + 16, position[1] + 16]
                            elif char == 'M': # Monstro

                                # Gera o monstro com base na dificuldade
                                if randint(0, 10) <= difficulty or initial_monster_ammount == 0:

                                    self.entities[f"Monster_{self.monster_ammount}"] = entities.Monster([position[0] + 16, position[1] + 16])
                                    self.monster_ammount += 1
                            
                            position[0] += 32 # Incrementa a posição latera
                        
                        # Ajusta as posições
                        position[0] = (screen_size[0] - room_size[0] * 32) / 2
                        position[1] += 32
    
    def delete(self):

        '''
        Libera os sprites
        '''

        for key in self.entities:

            self.entities[key].delete()
        
        self.collision_sprites.empty()
        self.trigger_sprites.empty()
        self.sprites.empty()
                
def generate_dungeon(screen_size, width = 1, heigth = 1):

    '''
    Gera uma dungeon que se comporta como labirinto

    Cada sala é representada como uma lista de quatro elementos, esses elementos definem as
    portas.
    '''

    structure = []
    
    # Gera a matriz de estrutura de portas
    for i in range(heigth):

        structure.append([])
        for _ in range(width):

            structure[i].append([False] * 4)

    room_struct_list = [] # Lista para as salas
    rooms_struct_stack = [] # Stack para as salas

    # Posição inicial na matriz de geração
    position = [randint(0, width - 1), randint(0, heigth - 1)]

    back_tracking = False # Define se o gerador está voltando no caminho ou não

    while True:

        directions = [] # Define as direções disponíveis para esta posição na matriz

        if not back_tracking: # Quando o gerador não está voltando a posição é armazenada

            room_struct_list.append(position[:])
            rooms_struct_stack.append(position[:])

        if len(room_struct_list) >= width * heigth: # Caso todas as posições sejam processadas termina o loop

            break
        
        # Caso seja possível ir para cima
        if position[1] > 0 and ([position[0], position[1] - 1] not in room_struct_list) and not (structure[position[1]][position[0]][0] or structure[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        # Caso seja possível ir para baixo
        if position[1] < heigth - 1 and ([position[0], position[1] + 1] not in room_struct_list) and not (structure[position[1]][position[0]][1] or structure[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        # Caso seja possível ir para a direita
        if position[0] < width - 1 and ([position[0] + 1, position[1]] not in room_struct_list) and not (structure[position[1]][position[0]][2] or structure[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        # Caso seja possível ir para a esquerda
        if position[0] > 0 and ([position[0] - 1, position[1]] not in room_struct_list) and not (structure[position[1]][position[0]][3] or structure[position[1]][position[0] - 1][2]):

            directions.append(Direction.LEFT)

        if len(directions) == 0: # Caso não seja possível ir para nenhuma direção

            back_tracking = True

            # Remove a última posição do stack
            rooms_struct_stack.remove(rooms_struct_stack[-1])

            # Volta uma posição
            position = rooms_struct_stack[-1]
        else:

            back_tracking = False
            direction = choice(directions) # Escolhe uma direção para ir

            if direction == Direction.UP: # Vai para cima

                structure[position[1]][position[0]][0] = True
                structure[position[1] - 1][position[0]][1] = True

                position[1] -= 1
            elif direction == Direction.DOWN: # Vai para baixo

                structure[position[1]][position[0]][1] = True
                structure[position[1] + 1][position[0]][0] = True

                position[1] += 1
            elif direction == Direction.RIGHT: # Vai para a direita

                structure[position[1]][position[0]][2] = True
                structure[position[1]][position[0] + 1][3] = True

                position[0] += 1
            else: # Vai para a esquerda

                structure[position[1]][position[0]][3] = True
                structure[position[1]][position[0] - 1][2] = True

                position[0] -= 1
    
    rooms = [] # Lista de salas
    initial_monster_ammount = 0 # Quantidade de monstros

    # Define uma sala aleatória para o jogador começar
    player_col = randint(0, width - 1)
    player_ln = randint(0, heigth - 1)

    # Cria cada objeto de sala
    for i in range(heigth):

        rooms.append([])
        for j in range(width):

            room = Room(structure[i][j], choice(os.listdir("Rooms")), screen_size, abs(i - player_ln) + abs(j - player_col), initial_monster_ammount)
            
            initial_monster_ammount += room.monster_ammount # Soma a quantidade de monstros

            rooms[i].append(room)

    # Cria o jogador
    player = entities.Player(rooms[player_ln][player_col].player_spawn_position)

    # Coloca o jogador na sala
    rooms[player_ln][player_col].entities["Player"] = player

    return player, rooms, [player_ln, player_col], initial_monster_ammount
