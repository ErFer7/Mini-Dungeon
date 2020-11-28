# -*- coding: utf-8 -*-

'''
Este módulo gerencia a interface do usuário (UI)
'''

import os

from enum import Enum
from math import ceil

import pygame
import graphics

class Alignment(Enum):

    CENTER = 1
    TOP_LEFT = 2
    TOP_RIGHT = 3

class UIBase():

    position: list
    screen_size: list
    texts: list
    buttons: dict
    surface: pygame.Surface((0, 0))
    selection_sound: pygame.mixer.Sound

    def __init__(self, position, size, screen_size):

        self.position = position[:]
        self.screen_size = screen_size[:]
        self.texts = []
        self.buttons = {}
        self.surface = pygame.Surface(size)
        self.selection_sound = pygame.mixer.Sound(os.path.join("Audio", "Selection.wav"))
    
    def update(self, display):

        self.surface.fill((20, 20, 20))

        for key in self.buttons:

            self.buttons[key].sprites.draw(self.surface)
        
        for text in self.texts:

            self.surface.blit(text.text, text.position)
        
        display.blit(self.surface, self.position)

        pygame.display.update()
    
    def check_buttons(self, click_position):

        for key in self.buttons:

            if self.buttons[key].is_clicked(click_position):

                return key
    
    def delete(self):

        for button in self.buttons:

            button.delete()

class Button():

    position: list
    size: list
    sprites: pygame.sprite.RenderPlain()

    def __init__(self, alignment, position, size, screen_size):

        self.position = [0, 0]
        self.size = size[:]
        self.sprites = pygame.sprite.RenderPlain()

        if alignment == Alignment.TOP_LEFT:

            self.position = position[:]
        elif alignment == Alignment.TOP_RIGHT:

            self.position = (screen_size[0] - position[0], position[1])
        else:

            self.position = ((screen_size[0] - size[0]) / 2 + position[0], (screen_size[1] - size[1]) / 2 - position[1])
        
        self.sprites.add(graphics.RectangleSprite(self.position, size, (255, 223, 0)))
        self.sprites.add(graphics.RectangleSprite((self.position[0] + 10, self.position[1] + 10), (size[0] - 20, size[1] - 20), (20, 20, 20)))
    
    def is_clicked(self, click_position):

        if click_position[0] >= self.position[0]                        \
            and click_position[0] <= self.position[0] + self.size[0]    \
            and click_position[1] >= self.position[1]                   \
            and click_position[1] <= self.position[1] + self.size[1]:

            return True
        else:

            return False
    
    def delete(self):

        self.sprites.empty()

class Text():

    size: int
    position: list
    font: pygame.font.Font
    text: pygame.font.Font.render
    color: pygame.color.Color

    def __init__(self, text, alignment, position, size, color, screen_size, font = "joystix monospace.ttf"):

        self.size = size
        self.position = [0, 0]
        self.color = pygame.color.Color(color)
        self.font = pygame.font.Font(os.path.join("Fonts", font), self.size)
        self.text = self.font.render(text, False, self.color)

        if alignment == Alignment.TOP_LEFT:

            self.position = position[:]
        elif alignment == Alignment.TOP_RIGHT:

            self.position = (screen_size[0] - position[0], position[1])
        else:

            self.position = ((screen_size[0] - self.text.get_rect().width) / 2 + position[0], (screen_size[1] - self.text.get_rect().height) / 2 - position[1])
    
    def update(self, text):

        self.text = self.font.render(text, False, self.color)

class Background():

    sprites: pygame.sprite.RenderPlain

    def __init__(self, size):

        self.sprites = pygame.sprite.RenderPlain()

        for i in range(ceil(size[1] / 256.0)):

            for j in range(ceil(size[0] / 256.0)):
                
                self.sprites.add(graphics.BackgroundSprite((j * 256.0, i * 256.0)))
    
    def delete(self):

        self.sprites.empty()

class Bar():

    position: list
    sprites: pygame.sprite.RenderPlain

    def __init__(self, alignment, position, size, border_color, color, screen_size):

        self.position = [0, 0]
        self.size = size
        self.sprites = pygame.sprite.RenderPlain()

        if alignment == Alignment.TOP_LEFT:

            self.position = position[:]
        elif alignment == Alignment.TOP_RIGHT:

            self.position = (screen_size[0] - position[0], position[1])
        else:

            self.position = ((screen_size[0] - self.size[0]) / 2 + position[0], (screen_size[1] - self.size[1]) / 2 - position[1])

        self.sprites.add(graphics.RectangleSprite((self.position[0] - 5, self.position[1] - 5), (self.size[0] + 10, self.size[1] + 10), border_color))
        self.sprites.add(graphics.RectangleSprite(self.position, self.size, color))
    
    def update(self, value):

        self.sprites.sprites()[1].update(self.position, [int((self.size[0] / 100.0) * value), 35])
    
    def delete(self):

        self.sprites.empty()

class Menu(UIBase):

    background: Background

    def __init__(self, screen_size, version):

        super().__init__((0, 0), screen_size, screen_size)

        self.background = Background(screen_size)

        self.buttons["Play"] = Button(Alignment.CENTER, (0, 0), (400, 100), screen_size)
        self.buttons["Quit"] = Button(Alignment.CENTER, (0, -200), (400, 100), screen_size)

        self.texts.append(Text("V {0}".format(version), Alignment.TOP_LEFT, (0, 0), 15, (255, 255, 255), screen_size))
        self.texts.append(Text("MINI DUNGEON", Alignment.CENTER, (0, 200), 80, (20, 20, 20), screen_size))
        self.texts.append(Text("MINI DUNGEON", Alignment.CENTER, (-10, 200), 80, (255, 223, 0), screen_size))
        self.texts.append(Text("JOGAR", Alignment.CENTER, (0, 0), 40, (255, 223, 0), screen_size))
        self.texts.append(Text("SAIR", Alignment.CENTER, (0, -200), 40, (255, 223, 0), screen_size))

    def update(self, display):

        self.surface.fill((20, 20, 20))
        self.background.sprites.draw(self.surface)

        for key in self.buttons:

            self.buttons[key].sprites.draw(self.surface)
        
        for text in self.texts:

            self.surface.blit(text.text, text.position)
        
        display.blit(self.surface, self.position)
    
    def delete(self):

        for button in self.buttons:

            button.delete()

        self.background.delete()

class LoadingScreen(UIBase):

    def __init__(self, screen_size):

        super().__init__((0, 0), screen_size, screen_size)

        self.texts.append(Text("Carregando...", Alignment.CENTER, (0, 0), 80, (255, 223, 0), screen_size))

class PauseScreen(UIBase):

    def __init__(self, screen_size):

        super().__init__((0, 0), screen_size, screen_size)

        self.texts.append(Text("PAUSADO", Alignment.CENTER, (0, 200), 80, (255, 223, 0), screen_size))

        self.buttons["Continue"] = Button(Alignment.CENTER, (0, 0), (400, 100), screen_size)
        self.buttons["Menu"] = Button(Alignment.CENTER, (0, -200), (400, 100), screen_size)

        self.texts.append(Text("CONTINUAR", Alignment.CENTER, (0, 0), 40, (255, 223, 0), screen_size))
        self.texts.append(Text("MENU", Alignment.CENTER, (0, -200), 40, (255, 223, 0), screen_size))

class GameOverScreen(UIBase):

    def __init__(self, screen_size):

        super().__init__((0, 0), screen_size, screen_size)

        self.texts.append(Text("FIM DE JOGO", Alignment.CENTER, (0, 200), 80, (255, 0, 0), screen_size))

        self.buttons["Restart"] = Button(Alignment.CENTER, (0, 0), (600, 100), screen_size)
        self.buttons["Menu"] = Button(Alignment.CENTER, (0, -200), (600, 100), screen_size)

        self.texts.append(Text("TENTAR NOVAMENTE", Alignment.CENTER, (0, 0), 40, (255, 223, 0), screen_size))
        self.texts.append(Text("MENU", Alignment.CENTER, (0, -200), 40, (255, 223, 0), screen_size))

class VictoryScreen(UIBase):

    def __init__(self, screen_size):

        super().__init__((0, 0), screen_size, screen_size)

        self.texts.append(Text("NÍVEL CONCLUÍDO", Alignment.CENTER, (0, 200), 80, (255, 223, 0), screen_size))

        self.buttons["Next"] = Button(Alignment.CENTER, (0, 0), (600, 100), screen_size)
        self.buttons["Menu"] = Button(Alignment.CENTER, (0, -200), (600, 100), screen_size)

        self.texts.append(Text("PRÓXIMO NÍVEL", Alignment.CENTER, (0, 0), 40, (255, 223, 0), screen_size))
        self.texts.append(Text("MENU", Alignment.CENTER, (0, -200), 40, (255, 223, 0), screen_size))

class FinalVictoryScreen(UIBase):

    def __init__(self, screen_size):

        super().__init__((0, 0), screen_size, screen_size)

        self.texts.append(Text("JOGO CONCLUÍDO", Alignment.CENTER, (0, 200), 80, (255, 223, 0), screen_size))

        self.buttons["Menu"] = Button(Alignment.CENTER, (0, 0), (600, 100), screen_size)
        self.buttons["Quit"] = Button(Alignment.CENTER, (0, -200), (600, 100), screen_size)

        self.texts.append(Text("MENU", Alignment.CENTER, (0, 0), 40, (255, 223, 0), screen_size))
        self.texts.append(Text("SAIR", Alignment.CENTER, (0, -200), 40, (255, 223, 0), screen_size))

class HUD(UIBase):

    life_bar: Bar
    progress_bar: Bar

    def __init__(self, screen_size):

        super().__init__((0, 0), (screen_size[0], 150), screen_size)

        self.life_bar = Bar(Alignment.TOP_LEFT, (10, 20), (500, 35), (100, 0, 0), (200, 0, 0), screen_size)
        self.progress_bar = Bar(Alignment.TOP_LEFT, (10, 80), (500, 35), (0, 0, 100), (0, 0, 200), screen_size)

        self.texts.append(Text("", Alignment.TOP_LEFT, (15, 27), 15, (255, 255, 255), screen_size))
        self.texts.append(Text("", Alignment.TOP_LEFT, (15, 87), 15, (255, 255, 255), screen_size))
        self.texts.append(Text("", Alignment.TOP_RIGHT, (120, 0), 15, (255, 255, 255), screen_size))
        self.texts.append(Text("", Alignment.TOP_RIGHT, (160, 20), 15, (255, 255, 255), screen_size))
        self.texts.append(Text("", Alignment.TOP_RIGHT, (160, 40), 15, (255, 255, 255), screen_size))
    
    def update(self, display, life, kill_count, FPS, room, monster_ammount, level, max_level):

        self.surface.fill((20, 20, 20))
        
        self.life_bar.update(life)
        self.life_bar.sprites.draw(self.surface)

        self.progress_bar.update((kill_count / monster_ammount) * 100.0)
        self.progress_bar.sprites.draw(self.surface)

        self.texts[0].update("Vida: {0}".format(int(life)))
        self.texts[1].update("{0}/{1} Monstros eliminados".format(kill_count, monster_ammount))
        self.texts[2].update("{0:.2f} FPS".format(FPS))
        self.texts[3].update(room)
        self.texts[4].update("Nível: {0}/{1}".format(level, max_level))

        for text in self.texts:

            self.surface.blit(text.text, text.position)
        
        display.blit(self.surface, self.position)

        pygame.display.update()

    def delete(self):

        self.life_bar.delete()