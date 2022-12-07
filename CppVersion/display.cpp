#include "display.h"
#include "math.h"

Display::Display(){
    this->window = openWindow(WIDTH, HEIGHT, "Othello");
}

void Display::drawBoard() {
    setBackGround(GREEN);
    for(int i = 0; i < 64; i++) {
        drawRect(IntPoint2(100 + 75 * (i % 8), 100 + 75 * floor(i / 8)), 75, 75, BLACK, 4);
    }
}

void Display::drawChips(vector<vector<int>> chips) {
    for(int row = 0; row < chips.size(); row++) {
        for(int col = 0; col < chips[0].size(); col++) {
            if(chips[row][col] == 1) {
                fillCircle(IntPoint2(100 + 75 * row + 37, 100 + 75 * col + 37), 30, BLACK);
            }
            if(chips[row][col] == -1) {
                fillCircle(IntPoint2(100 + 75 * row + 37, 100 + 75 * col + 37), 30, WHITE);
            }
            if(chips[row][col] == 2) {
                drawCircle(IntPoint2(100 + 75 * row + 37, 100 + 75 * col + 37), 30, BLACK);
            }
        }
    }
}

void Display::drawChips(vector<vector<int>> chips, vector<int> lastChip) {
    drawChips(chips);
    fillCircle(IntPoint2(lastChip[0]*75 + 137, lastChip[1]*75 + 137), 5, RED);
}

void Display::drawScore(int scoreWhite, int scoreBlack) {
    drawString(IntPoint2(120,80), "Black:" + to_string(scoreBlack), BLACK, 20);
    drawString(IntPoint2(240,80), "White:" + to_string(scoreWhite), BLACK, 20);
}

void Display::drawResults(int scoreWhite, int scoreBlack) {
    if(scoreWhite == scoreBlack) {
        drawString(IntPoint2(400,80), "Its a draw!", BLACK, 20);
    } else {
        string winner = scoreWhite > scoreBlack ? "White" : "Black";
        drawString(IntPoint2(400,80), winner + " player won!", BLACK, 20);
    }
}

void Display::drawSettings(int aiColor) {
    setBackGround(GREEN);
    fillCircle(IntPoint2(WIDTH/2 - 100, HEIGHT/2 - 100), 25, WHITE);
    fillCircle(IntPoint2(WIDTH/2 + 100, HEIGHT/2 - 100), 25, BLACK);
    fillCircle(IntPoint2(WIDTH/2, HEIGHT/2 - 100), 25, GREY);
    drawCircle(IntPoint2(WIDTH/2 + aiColor*100, HEIGHT/2 - 100), 30, RED, 5);
    drawString(IntPoint2(WIDTH/2 - 15, HEIGHT/2 - 100 + 10), "2P", WHITE, 20);
    drawString(IntPoint2(WIDTH/2 + 100 - 12, HEIGHT/2 - 100 + 10), "AI", WHITE, 20);
    drawString(IntPoint2(WIDTH/2 - 100 - 12, HEIGHT/2 - 100 + 10), "AI", BLACK, 20);
    fillRect(IntPoint2(WIDTH/3, HEIGHT*2/3), WIDTH/3, 100, GREY);
    drawString(IntPoint2(WIDTH/3 + 45, HEIGHT*2/3 + 70), "START", WHITE, 50);
}

