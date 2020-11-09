from random import randint, choice
from enum import Enum

class Direction(Enum):

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

class Room():
    
    width = 0
    heigth = 0
    doors = []

    def __init__(self, width, heigth, *doors):

        self.width = width
        self.heigth = heigth
        self.doors = doors

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

        if position[1] > 0 and not ([position[0], position[1] - 1] in roomsList) and not (roomsMat[position[1]][position[0]][0] or roomsMat[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        if position[1] < heigth - 1 and not ([position[0], position[1] + 1] in roomsList) and not (roomsMat[position[1]][position[0]][1] or roomsMat[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        if position[0] < width - 1 and not ([position[0] + 1, position[1]] in roomsList) and not (roomsMat[position[1]][position[0]][2] or roomsMat[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        if position[0] > 0 and not ([position[0] - 1, position[1]] in roomsList) and not (roomsMat[position[1]][position[0]][3] or roomsMat[position[1]][position[0] - 1][2]):

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
        for _ in range(width):

            rooms[i].append(Room(randint(10, 20), randint(10, 20), roomsMat[heigth][width]))

    return rooms