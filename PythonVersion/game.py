from utils.constants import WHITE, BLACK, AVAILABLE, DIRECTIONS, opposite, inside
from display import Display
import pygame
import math
import numpy as np


def set_chips():
    chips = np.ndarray(shape=(8, 8), dtype=object)
    chips[3][3] = WHITE
    chips[3][4] = BLACK
    chips[4][3] = BLACK
    chips[4][4] = WHITE
    return chips


def get_chip(chips, pos):
    return chips[pos[0]][pos[1]] if inside(pos) else None


def set_available(chips, color):
    for row in range(len(chips)):
        for col in range(len(chips[0])):
            pos_0 = np.array([row, col])
            if get_chip(chips, pos_0) == AVAILABLE:
                chips[row][col] = None
            if get_chip(chips, pos_0) is None:
                for direction in DIRECTIONS:
                    pos = pos_0 + direction
                    while get_chip(chips, pos) == opposite(color):
                        pos += direction
                        if get_chip(chips, pos) == color:
                            chips[row][col] = AVAILABLE
    return chips


def add_chip(pos_0, chips, color):
    chips[pos_0[0]][pos_0[1]] = color
    for direction in DIRECTIONS:
        pos = pos_0 + direction
        if get_chip(chips, pos) == opposite(color):
            pos += direction
            while get_chip(chips, pos) == opposite(color):
                pos += direction
            if get_chip(chips, pos) == color:
                while pos[0] != pos_0[0] or pos[1] != pos_0[1]:
                    chips[pos[0]][pos[1]] = color
                    pos -= direction
    return chips


def game_finished(chips):
    for row in range(len(chips)):
        for col in range(len(chips[0])):
            if chips[row][col] == AVAILABLE:
                return False
    return True


def print_result(chips):
    white, black = 0, 0
    for row in range(len(chips)):
        for col in range(len(chips[0])):
            if chips[row][col] == WHITE:
                white += 1
            if chips[row][col] == BLACK:
                black += 1
    print("Player with", "white" if white > black else "black", f"won {max(white, black)} to {min(white, black)}")


def start_game():
    display = Display()
    run = True
    chips = set_chips()
    turn = BLACK
    chips = set_available(chips, turn)
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.MOUSEBUTTONUP:
                row = math.floor((pygame.mouse.get_pos()[0] - 100) / 75)
                col = math.floor((pygame.mouse.get_pos()[1] - 100) / 75)
                pos = np.array([row, col])
                if get_chip(chips, pos) == AVAILABLE:
                    chips = add_chip(pos, chips, turn)
                    turn = opposite(turn)
                    chips = set_available(chips, turn)
                    if game_finished(chips):
                        run = False
        display.draw(chips)
    print_result(chips)
    pygame.quit()
