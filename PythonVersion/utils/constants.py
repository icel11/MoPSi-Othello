import numpy as np

GAME_TITLE = "Othello"
SIZE = 800
GREEN = (15, 100, 15)
AVAILABLE = (50, 50, 50)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
DIRECTIONS = [np.array([0, 1]),
              np.array([-1, 1]),
              np.array([-1, 0]),
              np.array([-1, -1]),
              np.array([0, -1]),
              np.array([1, -1]),
              np.array([1, 0]),
              np.array([1, 1])]


def opposite(color):
    return BLACK if color == WHITE else WHITE


def inside(pos):
    return 0 <= pos[0] < 8 and 0 <= pos[1] < 8
