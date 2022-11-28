#include "gamedisplay.h"
#include "math.h"

GameDisplay::GameDisplay(){
    this->window = openWindow(WIDTH, HEIGHT, "Othello");
}

void GameDisplay::drawBoard() {
    setBackGround(GREEN);
    for(int i = 0; i < 64; i++) {
        drawRect(IntPoint2(100 + 75 * (i % 8), 100 + 75 * floor(i / 8)), 75, 75, BLACK, 4);
    }
}

void GameDisplay::drawChips(vector<vector<int>> chips) {
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

void GameDisplay::drawScore(int scoreWhite, int scoreBlack) {
    drawString(IntPoint2(120,80), "Black:" + to_string(scoreBlack), BLACK, 20);
    drawString(IntPoint2(240,80), "White:" + to_string(scoreWhite), BLACK, 20);
}

void GameDisplay::drawResults(int scoreWhite, int scoreBlack) {
    if(scoreWhite == scoreBlack) {
        drawString(IntPoint2(400,80), "Its a draw!", BLACK, 20);
    } else {
        string winner = scoreWhite > scoreBlack ? "White" : "Black";
        drawString(IntPoint2(400,80), winner + " player won!", BLACK, 20);
    }
}
