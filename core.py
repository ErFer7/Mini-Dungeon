# -*- coding: utf-8 -*-

from enum import Enum

class State(Enum):

    '''
    Definição dos estados do jogo
    '''

    MENU = 1
    INGAME = 2
    PAUSED = 3
    WON = 4
    LOST = 5
    FINISHED = 6
    RESTARTING = 7
    EXITING = 8

class GameState():

    level: int
    max_level: int
    state: State

    def __init__(self, state, level, max_level):

        self.state = state
        self.level = level
        self.max_level = max_level