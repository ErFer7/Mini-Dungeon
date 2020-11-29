# -*- coding: utf-8 -*-

'''
Neste módulo estão definidas as entidades
'''

import os

from enum import Enum
from math import sqrt
from random import randint

import pygame
import graphics

class EntityState(Enum):

    '''
    Estados da entidade
    '''

    IDLING = 1
    ATTACKING = 2
    STUNNED = 3
    DEAD = 4

class Entity():

    '''
    As entidades são o jogador, monstros e poções de vida
    '''

    position: list # Posição da entidade
    direction: list # Direção
    velocity: list # Valocidade
    drag: float # Arrasto
    speed: float # Aceleração
    life: int # Vida
    _power: float # Poder de dano
    _attack_time: float # Tempo de ataque
    _attack_time_counter: int # Contador do tempo de ataque
    _stun_time: float # Tempo de atordoamento
    _stun_time_counter: int # Contador do tempo de atordoamento
    _state: EntityState # Estado
    sprites: pygame.sprite.RenderPlain # Sprites
    attack_sound: pygame.mixer.Sound # Som de ataque
    collision_sound: pygame.mixer.Sound # Som de colisão

    def __init__(self, position):

        # Inicializa todas as variáveis
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

        '''
        Define o estado como "atacando"
        '''

        self._state = EntityState.ATTACKING

    def change_life(self, value):

        '''
        Muda o valor de vida
        '''

        self.life += value

        if value < 0: # Caso esteja levando dano

            self._state = EntityState.STUNNED

        if self.life <= 0.0: # Caso de morte

            self.life = 0.0
            self._state = EntityState.DEAD
        elif self.life > 100.0: # Caso de recuperação de vida acima do limite

            self.life = 100.0
    
    def is_attacking(self):

        '''
        Método para determinar se a entidade está atacando
        '''

        if self._state == EntityState.ATTACKING:

            return True
        else:

            return False
    
    def is_dead(self):

        '''
        Método para determinar se a entidade está morta
        '''

        if self._state == EntityState.DEAD:

            return True
        else:

            return False

    def delete(self):

        '''
        Libera os sprites
        '''

        if len(self.sprites.sprites()) > 0:

            self.sprites.sprites()[0].entity_sprites.empty()
        self.sprites.empty()

class Player(Entity):

    '''
    Define o jogador
    '''

    kill_count: int # Contagem de eliminações
    game_over_sound: pygame.mixer.Sound # Som de fim de jogo
    kill_sound: pygame.mixer.Sound # Som eliminação

    def __init__(self, position):

        super().__init__(position)

        # Inicializa as variáveis
        self.speed = 2.0
        self._stun_time = 0.1
        self.power = 3.5
        self.kill_count = 0
        self.attack_sound = pygame.mixer.Sound(os.path.join("Audio", "Sword attack.wav"))
        self.game_over_sound = pygame.mixer.Sound(os.path.join("Audio", "Game over.wav"))
        self.kill_sound = pygame.mixer.Sound(os.path.join("Audio", "Kill.wav"))
        self.sprites.add(graphics.PlayerBaseSprite((self.position[0] - 16, self.position[1] - 16)))
    
    def update(self, event):

        '''
        Atualiza os controles e definições do jogador
        '''

        # Caso o jogador não esteja atordoado e o evento não seja "Nulo"
        if event is not None and self._state != EntityState.STUNNED:

            if event.type == pygame.KEYDOWN: # Caso uma tecla esteja sendo pressionada
                    
                if event.key == pygame.K_a: # Tecla "A". Movimento para a esquerda

                    self.direction[0] = -1
                    self.velocity[0] = -self.speed
                elif event.key == pygame.K_d: # Tecla "D". Movimento para a direita

                    self.direction[0] = 1
                    self.velocity[0] = self.speed
                    
                if event.key == pygame.K_s: # Tecla "S". Movimento para baixo

                    self.direction[1] = 1
                    self.velocity[1] = self.speed
                elif event.key == pygame.K_w: # Tecla "W". Movimento para cima

                    self.direction[1] = -1
                    self.velocity[1] = -self.speed
                
                if event.key == pygame.K_k and not self.is_attacking(): # tecla "K". Ataque

                    self.attack()
                
            if event.type == pygame.KEYUP: # Caso uma tecla seja solta

                if event.key == pygame.K_a or event.key == pygame.K_d: # Teclas horizontais

                    self.direction[0] = 0
                    
                if event.key == pygame.K_s or event.key == pygame.K_w: # Teclas verticais

                    self.direction[1] = 0
        elif self._state == EntityState.STUNNED: # Redefine as direções caso o jogador esteja artodoado

            self.direction[0] = 0
            self.direction[1] = 0
        
        if self._state == EntityState.ATTACKING: # Faz a contagem do ataque e o redefine caso necessário

            self._attack_time_counter += 1

            if self._attack_time_counter > 60 * self._attack_time:

                self._attack_time_counter = 0
                self._state = EntityState.IDLING
        elif self._state == EntityState.STUNNED: # Faz a contagem do atordoamento e o redefine caso necessário

            self._stun_time_counter += 1

            if self._stun_time_counter > 60 * self._stun_time:

                self._stun_time_counter = 0
                self._state = EntityState.IDLING

class Monster(Entity):

    '''
    Define o monstro
    '''

    _sight_distance: float # Define a distância de visão

    def __init__(self, position):

        super().__init__(position)

        # Inicializa as variáveis
        self.power = 4.5
        self.speed = 1.0
        self._stun_time = 0.1
        self._sight_distance = 400.0
        self.attack_sound = pygame.mixer.Sound(os.path.join("Audio", "Monster attack.wav"))
        self.sprites.add(graphics.MonsterBaseSprite((self.position[0] - 16, self.position[1] - 16)))
    
    def update(self, player_position, obstacles):
        
        '''
        Define o comportamento do monstro
        '''

        # Distância do jogador
        distance_from_player = sqrt((player_position[0] - self.position[0]) ** 2 +
                                    (player_position[1] - self.position[1]) ** 2)

        # Caso o monstro esteja perto o suficiente do jogador e não esteja nem morto ou atordoado
        if distance_from_player <= self._sight_distance and \
           self._state != EntityState.DEAD and              \
           self._state != EntityState.STUNNED:

            has_line_of_sight = True # Definição da linha de visão

            ang_coeff = 0.0 # Coeficiente angular da linha de visão

            # Características da linha
            is_vertical = False
            is_horizontal = False

            if (player_position[0] - self.position[0]) == 0.0: # Caso a variação de X seja 0

                is_vertical = True
            elif (self.position[1] - player_position[1]) == 0.0: # Caso a variação de Y seja 0

                is_horizontal = True
            else:

                # Calcula o coeficiente angular
                ang_coeff = (self.position[1] - player_position[1]) / (player_position[0] - self.position[0])

            for obstacle in obstacles: # Loop para cada obstáculo
                
                # Definições do obstáculo
                obstacle_is_in_range_X = True
                obstacle_is_in_range_Y = True

                if player_position[0] >= self.position[0]: # Caso o jogador esteja na direita do monstro

                    # Se o obstáculo não está antes do monstro ou adiante do jogador
                    if obstacle.rect.right <= self.position[0] or obstacle.rect.left >= player_position[0]:

                        obstacle_is_in_range_X = False
                else: # Caso o jogador esteja na esquerda do monstro

                    # Se o obstáculo não está antes do monstro ou adiante do jogador
                    if obstacle.rect.left >= self.position[0] or obstacle.rect.right <= player_position[0]:

                        obstacle_is_in_range_X = False

                if -player_position[1] >= -self.position[1]: # Caso o jogador esteja acima do monstro

                    # Se o obstáculo não está antes do monstro ou adiante do jogador
                    if -obstacle.rect.top <= -self.position[1] or -obstacle.rect.bottom >= -player_position[1]:

                        obstacle_is_in_range_Y = False
                else: # Caso o jogador esteja abaixo do monstro

                    # Se o obstáculo não está antes do monstro ou adiante do jogador
                    if -obstacle.rect.bottom >= -self.position[1] or -obstacle.rect.top <= -player_position[1]:

                        obstacle_is_in_range_Y = False

                # Caso o obstáculo esteja no intervalo em que pode estar no caminho
                if obstacle_is_in_range_X and obstacle_is_in_range_Y:
                    
                    # Redefine os vértices
                    top_left = (obstacle.rect.topleft[0] - self.position[0], self.position[1] - obstacle.rect.topleft[1])
                    top_right = (obstacle.rect.topright[0] - self.position[0], self.position[1] - obstacle.rect.topright[1])
                    botton_right = (obstacle.rect.bottomright[0] - self.position[0], self.position[1] - obstacle.rect.bottomright[1])
                    botton_left = (obstacle.rect.bottomleft[0] - self.position[0], self.position[1] - obstacle.rect.bottomleft[1])

                    if is_horizontal: # Caso a linha seja horizontal
                        
                        if top_left[1] == 0: # Intercepta o topo

                            has_line_of_sight = False
                            break

                        if botton_left[1] == 0: # Intercepta o lado infeiror

                            has_line_of_sight = False
                            break

                        if botton_left[1] <= 0 and top_left[1] >= 0: # Intercepta a esquerda

                            has_line_of_sight = False
                            break

                        if botton_right[1] <= 0 and top_right[1] >= 0: # Intercepta a direita

                            has_line_of_sight = False
                            break
                    elif is_vertical: # Caso a linha seja vertical
                    
                        if top_left[0] <= 0 and top_right[0] >= 0: # Intercepta o topo
                            
                            has_line_of_sight = False
                            break

                        if botton_left[0] <= 0 and botton_right[0] >= 0: # Intercepta o lado infeiror
                            
                            has_line_of_sight = False
                            break

                        if botton_left[0] == 0: # Intercepta a esquerda

                            has_line_of_sight = False
                            break

                        if botton_right[0] == 0: # Intercepta a direita

                            has_line_of_sight = False
                            break
                    else: # Caso a linha seja uma linha comum

                        # Intercepta o topo
                        if top_left[1] / ang_coeff >= top_left[0] and \
                           top_right[1] / ang_coeff <= top_right[0]:
                            
                            has_line_of_sight = False
                            break
                        
                        # Intercepta o lado infeiror
                        if botton_left[1] / ang_coeff >= botton_left[0] and \
                           botton_right[1] / ang_coeff <= botton_right[0]:

                            has_line_of_sight = False
                            break
                        
                        # Intercepta a esquerda
                        if botton_left[0] * ang_coeff >= botton_left[1] and \
                           top_left[0] * ang_coeff <= top_left[1]:

                            has_line_of_sight = False
                            break
                        
                        # Intercepta a direita
                        if botton_right[0] * ang_coeff >= botton_right[1] and \
                           top_right[0] * ang_coeff <= top_right[1]:

                            has_line_of_sight = False
                            break

            if has_line_of_sight: # Caso o monstro tenha visão do jogador

                # Checa se o jogador precisa se mover horizontalmente
                if abs(player_position[0] - self.position[0]) > 3.0:

                    if self.position[0] < player_position[0]: # Se o jogador está na direita do monstro

                        self.direction[0] = 1   
                        self.velocity[0] = self.speed
                    elif self.position[0] > player_position[0]: # Se o jogador está na esquerda do monstro

                        self.direction[0] = -1
                        self.velocity[0] = -self.speed
                else:

                    self.direction[0] = 0

                # Checa se o jogador precisa se mover verticalmente
                if abs(player_position[1] - self.position[1]) > 3.0:

                    if self.position[1] < player_position[1]: # Se o jogador está acima do monstro

                        self.direction[1] = 1
                        self.velocity[1] = self.speed
                    elif self.position[1] > player_position[1]: # Se o jogador está abaixo do monstro

                        self.direction[1] = -1
                        self.velocity[1] = -self.speed
                else:

                    self.direction[1] = 0

                if distance_from_player <= 16 and not self.is_attacking(): # Verifica se pode atacar

                    self.attack() # Ataca o jogador
        else: # Redefine as direções para 0

            self.direction[0] = 0
            self.direction[1] = 0
        
        if self._state == EntityState.ATTACKING: # Faz a contagem do ataque e o redefine caso necessário

            self._attack_time_counter += 1

            if self._attack_time_counter > int(60 * self._attack_time):

                self._attack_time_counter = 0
                self._state = EntityState.IDLING
        elif self._state == EntityState.STUNNED: # Faz a contagem do atordoamento e o redefine caso necessário

            self._stun_time_counter += 1

            if self._stun_time_counter > 60 * self._stun_time:

                self._stun_time_counter = 0
                self._state = EntityState.IDLING
    
    def drop(self, entities, key):

        '''
        Calcula o drop
        '''

        if randint(0, 3) == 0: # Há 1/4 de chance de gerar uma poção de vida

            drop_key = key + "_drop"
            entities[drop_key] = HealthPotion(self.position)

class HealthPotion(Entity):

    '''
    Define uma poção de vida
    '''

    heal_sound: pygame.mixer.Sound # Define o som da poção

    def __init__(self, position):

        super().__init__(position)

        # Inicializa as variáveis
        self.heal_sound = pygame.mixer.Sound(os.path.join("Audio", "Heal.wav"))
        self.sprites.add(graphics.HealthPotionBaseSprite((self.position[0] - 16, self.position[1] - 16)))
