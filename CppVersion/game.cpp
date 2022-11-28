#include "game.h"

Game::Game()
{
    for(int row = 0; row < 8; row++) {
        vector<int> line;
        for(int col = 0; col < 8; col++) {
            line.push_back(0);
        }
        chips.push_back(line);
    }
    putChip(3,3,-1);
    putChip(3,4,1);
    putChip(4,3,1);
    putChip(4,4,-1);
    setAvailable(turn);
    display.drawBoard();
    display.drawScore(scoreWhite, scoreBlack);
    display.drawChips(chips);
}

void Game::putChip(int x, int y, int color, bool turned) {
    if(color == 1)
        scoreBlack++;
    if(color == -1)
        scoreWhite++;
    if(turned) {
        if(color == 1)
            scoreWhite--;
        if(color == -1)
            scoreBlack--;
    }
    chips[x][y] = color;
}

int Game::getChip(int x, int y) {
    if(x < 8 && x >= 0 && y < 8 && y >= 0) {
        return chips[x][y];
    }
    return 0;
}

void Game::setAvailable(int color) {
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(getChip(row, col) == 2){
                chips[row][col] = 0;
            }
            if(getChip(row, col) == 0){
                for(vector<int> direction : DIRECTIONS){
                    int posX = row + direction[0];
                    int posY = col + direction[1];
                    while(getChip(posX, posY) == -color){
                        posX += direction[0];
                        posY += direction[1];
                        if(getChip(posX, posY) == color) {
                            chips[row][col] = 2;
                        }
                    }
                }
            }
        }
    }
}

void Game::addChip(int posX_0, int posY_0, int color) {
    putChip(posX_0, posY_0, color);
    for(vector<int> direction : DIRECTIONS){
        int posX = posX_0 + direction[0];
        int posY = posY_0 + direction[1];
        if(getChip(posX, posY) == -color) {
            posX += direction[0];
            posY += direction[1];
            while(getChip(posX, posY) == -color){
                posX += direction[0];
                posY += direction[1];
            }
            if(getChip(posX, posY) == color) {
                while(posX != posX_0 || posY != posY_0) {
                    if(getChip(posX, posY) != color) {
                        putChip(posX, posY, color, true);
                    }
                    posX -= direction[0];
                    posY -= direction[1];
                }
            }
        }
    }
}

bool Game::noMove() {
    for(int row = 0; row < 8; row++)
        for(int col = 0; col < 8; col++)
            if(chips[row][col] == 2)
                return false;
    return true;
}

void Game::update(int posX, int posY) {
    if(posX > 100 && posY > 100) {
        int squareX = floor((posX - 100) / 75);
        int squareY = floor((posY - 100) / 75);
        if(chips[squareX][squareY] == 2) {
            addChip(squareX, squareY, turn);
            turn *= -1;
            setAvailable(turn);
            if(noMove()) {

                turn *= -1;
                setAvailable(turn);
                if(noMove()) {
                    finished = true;
                }
            }
        }
    }
}

void Game::draw() {
    display.drawBoard();
    display.drawChips(chips);
    display.drawScore(scoreWhite, scoreBlack);
    if(finished) {
        display.drawResults(scoreWhite, scoreBlack);
    }
}


void Game::exit() {
    clearWindow();
    closeWindow(display.getWindow());
}
