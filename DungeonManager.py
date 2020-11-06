from random import randint, choice
from enum import Enum

class Direction(Enum):

    UP = 1
    DOWN = 2
    RIGHT = 3
    LEFT = 4

def DungeonGenerator(size = 2):

    # Cima, Baixo, Direita e Esquerda
    roomsMat = [[[False, False, False, False]] * size] * size

    roomsList = []
    roomsStack = []

    position = [randint(0, size - 1), randint(0, size - 1)]

    while True:

        directions = []

        roomsList.append(position)
        roomsStack.append(position)

        if position[1] > 0 and not (roomsMat[position[1] - 1][position[0]] in roomsList) and not (roomsMat[position[1]][position[0]][0] or roomsMat[position[1] - 1][position[0]][1]):

            directions.append(Direction.UP)
        
        if position[1] < size - 1 and not (roomsMat[position[1] + 1][position[0]] in roomsList) and not (roomsMat[position[1]][position[0]][1] or roomsMat[position[1] + 1][position[0]][0]):

            directions.append(Direction.DOWN)
        
        if position[0] < size - 1 and not (roomsMat[position[1]][position[0] + 1] in roomsList) and not (roomsMat[position[1]][position[0]][2] or roomsMat[position[1]][position[0] + 1][3]):

            directions.append(Direction.RIGHT)
        
        if position[0] > 0 and not (roomsMat[position[1]][position[0] - 1] in roomsList) and not (roomsMat[position[1]][position[0]][3] or roomsMat[position[1]][position[0] - 1][2]):

            directions.append(Direction.LEFT)

        if directions.count == 0:

            roomsStack.remove(len(roomsStack) - 1)
        else:

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

                roomsMat[position[1]][position[0]][1] = True
                roomsMat[position[1]][position[0] + 1][3] = True

                position[0] += 1
            else:

                roomsMat[position[1]][position[0]][1] = True
                roomsMat[position[1]][position[0] - 1][2] = True

                position[0] -= 1
        
        if roomsList.count() >= size ** 2:

            roomsList.clear()
            roomsStack.clear()

            break
    
    print(roomsMat)