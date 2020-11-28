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
    RESTARTING = 6
    EXITING = 7

class GameState():

    state: State

    def __init__(self, state):

        self.state = state