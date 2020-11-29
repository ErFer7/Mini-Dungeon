# -*- coding: utf-8 -*-

'''
Neste módulo estão definidos todos os sprites e o funcionamento gráfico do jogo
'''

import os

from math import sin
from random import randint

import pygame

class RenderControl():

    '''
    Define um objeto que controla a renderização
    '''

    update_all: bool # Define se toda a tela deve ser atualizada ou não

    def __init__(self):

        self.update_all = False

    def update_graphics(self, room, display):

        '''
        Atualiza os gráficos
        '''

        if self.update_all: # renderiza toda a tela novamente

            display.fill((20, 20, 20))

            room.sprites.draw(display)
            room.collision_sprites.draw(display)
            room.collision_sprites.update()
            room.trigger_sprites.draw(display)

            self.update_all = False
        else:

            for key in room.entities: # Loop para cada entidade no dicionário

                overlap_group = pygame.sprite.RenderPlain() # Cria um grupo de sprites

                for group in [room.collision_sprites, room.trigger_sprites, room.sprites]: # Loop para cada grupo
                    
                    # Obtém uma lista com todos os sprites que o sprite de área de renderização da entidade
                    # está colidindo
                    overlap = pygame.sprite.spritecollide(room.entities[key].sprites.sprites()[0].render_area,
                                                          group,
                                                          False)

                    if overlap is not None: # Caso algum sprite colide

                        for sprite in overlap: # Para cada sprite na lista

                            overlap_group.add(sprite) #  Adiciona o sprite no grupo

                overlap_group.draw(display) # Renderiza o grupo
                overlap_group.empty() # Libera os sprites evitando o acúmulo de memória

            for key in room.entities: # Renderiza cada entidade

                room.entities[key].sprites.sprites()[0].entity_sprites.draw(display)

        pygame.display.update() # Atualiza a tela

class BackgroundSprite(pygame.sprite.Sprite):

    '''
    Sprite de plano de fundo do menu
    '''

    def __init__(self, position):

        super().__init__()

        random_number = 0

        if randint(0, 9) == 0: # 1/10 de chance de gerar um sprite que não seja a parede simples

            random_number = randint(1, 6)

        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall_{0}.png".format(random_number))), (256, 256))
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]

class RectangleSprite(pygame.sprite.Sprite):

    '''
    Define um sprite retangular
    '''

    def __init__(self, position, size, *color):

        super().__init__()

        # Inicializa as variáveis
        self.image = pygame.Surface(size)
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]
        self.image.fill(color)
    
    def update(self, position, size):

        '''
        Redefine o tamanho do sprite
        '''

        if size[0] == 0:

            size[0] = 1
        
        if size[1] == 0:

            size[1] = 1

        self.image = pygame.transform.scale(self.image, size)
        self.rect.x = position[0]
        self.rect.y = position[1]

class FloorSprite(pygame.sprite.Sprite):

    '''
    Define o sprite do chão
    '''

    def __init__(self, position, floor_type):

        super().__init__()

        # O sprite é definido com base no caractere do mapa

        if floor_type == '<':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 90)
        elif floor_type == '>':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), -90)
        elif floor_type == '^':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32))
        elif floor_type == 'v':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_border.png")), (32, 32)), 180)
        elif floor_type == 'q':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32))
        elif floor_type == 'w':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, False)
        elif floor_type == 'e':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), False, True)
        elif floor_type == 'r':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_corner.png")), (32, 32)), True, True)
        elif floor_type == 't':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32))
        elif floor_type == 'y':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), -90)
        elif floor_type == 'u':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 180)
        elif floor_type == 'i':

            self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor_detailed.png")), (32, 32)), 90)
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Floor", "Floor.png")), (32, 32))

        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]

class WallSprite(pygame.sprite.Sprite):

    '''
    Define o sprite da parede
    '''

    def __init__(self, position, wall_type):

        super().__init__()

        # O sprite é definido com base no caractere do mapa

        if wall_type == '#':
            
            random_number = 0

            if randint(0, 9) == 0: # 1/10 de chance de gerar uma parede diferente da simples

                random_number = randint(1, 11)

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall_{0}.png".format(random_number))), (32, 32))
        elif wall_type == '_':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top.png")), (32, 32))
        elif wall_type == '$':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Left.png")), (32, 32))
        elif wall_type == '%':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Right.png")), (32, 32))
        elif wall_type == '@':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Left.png")), (32, 32))
        elif wall_type == '+':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Left.png")), (32, 32)), False, True)
        elif wall_type == '-':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Right.png")), (32, 32)), False, True)
        elif wall_type == '=':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton.png")), (32, 32))
        elif wall_type == '[':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton - Left.png")), (32, 32))
        elif wall_type == ']':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Botton - Right.png")), (32, 32))
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Wall", "Wall - Top - Right.png")), (32, 32))
        
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]

class BoxSprite(pygame.sprite.Sprite):

    '''
    Define o sprite de caixa
    '''

    def __init__(self, position):

        super().__init__()

        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Obstacles", "Box.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]

class DoorSprite(pygame.sprite.Sprite):

    '''
    Define o sprite da porta
    '''

    direction: int # Define a direção da porta

    def __init__(self, position, direction, door_type):

        super().__init__()

        # O sprite é definido com base no caractere do mapa

        if door_type == '0':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door.png")), (32, 32))
        elif door_type == '1':

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Botton.png")), (32, 40))
        elif door_type == '2':

            self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Lateral.png")), (32, 32)), True, False)
        else:

            self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Doors", "Door - Lateral.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]
        self.direction = direction

class DecorationSprite(pygame.sprite.Sprite):

    '''
    Define o sprite da decoração (caveira)
    '''

    def __init__(self, position):

        super().__init__()

        flip = False

        if randint(0, 1) == 0: # 1/2 de chance de gerar virado em outra direção

            flip = True

        self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Decoration", "Skull.png")), (32, 32)), flip, False)
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]

class EntityBaseSprite(pygame.sprite.Sprite):

    '''
    Define a base dos sprites para entidades

    Essencialmente isso é uma hitbox
    '''

    entity_sprites: pygame.sprite.RenderPlain # Define os sprites
    item_sprite: pygame.sprite.Sprite # Define o sprite dos itens carregados pela entidade
    render_area: pygame.sprite.Sprite # Define a área de renderização
    _old_attacking_state: bool # Define o estado anterior do ataque

    def __init__(self, position):

        super().__init__()

        # Inicializa as variáveis
        self.image = pygame.Surface([32, 32])
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]
        self.entity_sprites = pygame.sprite.RenderPlain()
        self.render_area = RenderAreaSprite((self.rect.centerx, self.rect.centery), (48, 48))
        self._old_attacking_state = False
    
    def update(self, position, horizontal_orientation, attacking):

        '''
        Atualiza o sprite
        '''

        # Atualiza as posições
        self.rect.x = position[0] - 16
        self.rect.y = position[1] - 16

        # Atualiza a exibição dos itens
        if attacking != self._old_attacking_state:

            if attacking:

                self.entity_sprites.add(self.item_sprite)
            else:

                self.entity_sprites.remove(self.item_sprite)

        self._old_attacking_state = attacking

        # Atualiza os sprites contidos
        self.entity_sprites.update((position[0] - 16, position[1] - 16), horizontal_orientation)
        self.item_sprite.update((position[0] - 16, position[1] - 16), horizontal_orientation)
        self.render_area.update((self.rect.centerx, self.rect.centery))

class EntitySprite(pygame.sprite.Sprite):

    '''
    Define o sprite das entidades
    '''

    _old_horizontal_orientation: int # Define a orientação anterior do sprite
    walking_freq: float # Define a frequencia da caminhada
    walking_amp: float # Define a amplitude da caminhada

    def __init__(self, position):

        super().__init__()

        # Inicializa as variáveis
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]
        self._old_horizontal_orientation = 1
        self.walking_freq = 1.0
        self.walking_amp = 1.0
    
    def update(self, position, horizontal_orientation):
        
        '''
        Atualiza o sprite
        '''

        if abs(self.rect.x - position[0]) < 1.0: # Caso a variação em X seja mínima

            # Atualiza a posição vertical. A animação é feita com a função seno
            self.rect.y = position[1] + self.walking_amp * sin(position[1] * self.walking_freq)
        else:

            # Atualiza a posição vertical
            self.rect.y = position[1] + self.walking_amp * sin(position[0] * self.walking_freq)

        self.rect.x = position[0] # Atualiza a posição horizontal

        # Atualiza a orientação do sprite quando a orientação mudar
        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            
            self._old_horizontal_orientation = horizontal_orientation

class RenderAreaSprite(pygame.sprite.Sprite):

    '''
    Define o sprite da área de renderização
    '''

    def __init__(self, position, size):

        super().__init__()

        # Inicializa as variáveis
        self.image = pygame.Surface(size)
        self.rect = self.image.get_rect()
        self.rect.centerx = position[0]
        self.rect.centery = position[1]

    def update(self, position):

        '''
        Atualiza a posição do sprite
        '''

        self.rect.centerx = position[0]
        self.rect.centery = position[1]

class PlayerBaseSprite(EntityBaseSprite):

    '''
    Definição do sprite de base do jogador
    '''

    def __init__(self, position):

        super().__init__(position)

        self.entity_sprites.add(PlayerSprite(position))
        self.render_area = RenderAreaSprite((self.rect.centerx, self.rect.centery), (56, 56))
        self.item_sprite = SwordSprite(position)

class MonsterBaseSprite(EntityBaseSprite):

    '''
    Definição do sprite de base dos monstros
    '''

    def __init__(self, position):

        super().__init__(position)

        self.entity_sprites.add(MonsterSprite(position))
        self.item_sprite = SwordSprite(position)

    def update(self, position, horizontal_orientation, attacking):

        '''
        Atualiza o sprite
        '''

        self.rect.x = position[0] - 16
        self.rect.y = position[1] - 16

        self.entity_sprites.update((position[0] - 16, position[1] - 16), horizontal_orientation)
        self.render_area.update((self.rect.centerx, self.rect.centery))

class HealthPotionBaseSprite(EntityBaseSprite):

    '''
    Definição do sprite de base da poção de vida
    '''

    def __init__(self, position):

        super().__init__(position)

        self.entity_sprites.add(HealthPotionSprite(position))

class PlayerSprite(EntitySprite):

    '''
    Definição do sprite do jogador
    '''

    def __init__(self, position):

        super().__init__(position)
        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Chars", "Char_0.png")), (32, 32))
        self.walking_freq = 0.25
        self.walking_amp = 2.0

class MonsterSprite(EntitySprite):

    '''
    Definição do sprite dos monstros
    '''

    def __init__(self, position):

        super().__init__(position)
        self.image = pygame.transform.flip(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Monsters", "Monster_{0}.png".format(randint(0, 24)))), (32, 32)), True, False)
        self.walking_freq = 0.5
        self.walking_amp = 2.0

class SwordSprite(pygame.sprite.Sprite):

    '''
    Definição do sprite da espada
    '''

    _old_horizontal_orientation: int # Orientação anterior

    def __init__(self, position):

        super().__init__()

        self.image = pygame.transform.rotate(pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Itens", "Sword.png")), (14, 28)), -90)
        self.rect = self.image.get_rect()
        self.rect.x = position[0] + 14
        self.rect.y = position[1] + 16
        self._old_horizontal_orientation = 1
    
    def update(self, position, horizontal_orientation):

        '''
        Atualiza o sprite com base na orientação e posição
        '''

        # A posição horizontal depende da orientação do jogador

        if self._old_horizontal_orientation == 1:

            self.rect.x = position[0] + 14
        else:

            self.rect.x = position[0] - 14
        self.rect.y = position[1] + 16

        if horizontal_orientation != 0 and self._old_horizontal_orientation != horizontal_orientation:

            if horizontal_orientation < 0 and self._old_horizontal_orientation >= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            elif horizontal_orientation > 0 and self._old_horizontal_orientation <= 0:

                self.image = pygame.transform.flip(self.image, True, False)
            self._old_horizontal_orientation = horizontal_orientation

class HealthPotionSprite(pygame.sprite.Sprite):

    '''
    Define o sprite da poção de cura
    '''

    def __init__(self, position):

        super().__init__()

        self.image = pygame.transform.scale(pygame.image.load(os.path.join("Sprites", "Itens", "Health_Potion.png")), (32, 32))
        self.rect = self.image.get_rect()
        self.rect.x = position[0]
        self.rect.y = position[1]