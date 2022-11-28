from utils.constants import *
import math
import pygame


class Display:

    def __init__(self):
        self.WIN = pygame.display.set_mode((SIZE, SIZE))
        pygame.display.set_caption(GAME_TITLE)

    def draw_board(self):
        for i in range(64):
            pygame.draw.rect(self.WIN, BLACK, (100 + 75 * (i % 8), 100 + 75 * math.floor(i / 8), 75, 75), 2)

    def draw_chips(self, chips):
        for row in range(len(chips)):
            for col in range(len(chips[0])):
                chip = chips[row][col]
                if chip is not None:
                    pygame.draw.circle(self.WIN, chip, (100 + 75 * row + 37, 100 + 75 * col + 37), 30)

    def draw(self, chips):
        self.WIN.fill(GREEN)
        self.draw_board()
        self.draw_chips(chips)
        pygame.display.update()
