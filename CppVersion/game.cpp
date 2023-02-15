#include "game.h"
#include <map>
#include <limits.h>

Game::Game(int aiColor)
{
    vector<vector<int>> chips;
    for(int row = 0; row < 8; row++) {
        vector<int> line(8);
        chips.push_back(line);
    }
    chips[3][3] = -1;
    chips[3][4] = 1;
    chips[4][3] = 1;
    chips[4][4] = -1;

    gamePosition = Position(chips, turn);
    this->aiColor = aiColor;
    draw();
}

void Game::changeTurn() {
    turn *= -1;
    gamePosition.setAvailable(turn);
}

int Game::getWeightMatrixScore(Position position, int row, int col) {
    if(((row == 1 and col == 0) or (row == 0 and col == 1) or (row == 1 and col == 1)) and abs(position.get(0,0)) == 1) {
        return 2;
    }
    if(((row == 0 and col == 6) or (row == 1 and col == 6) or (row == 1 and col == 7)) and abs(position.get(0,7)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 0) or (row == 6 and col == 1) or (row == 7 and col == 1)) and abs(position.get(7,0)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 7) or (row == 7 and col == 6) or (row == 6 and col == 6)) and abs(position.get(7,7)) == 1) {
        return 2;
    }
    return weightMatrix[row][col];
}

int Game::calculateScore(Position position) {
    int score = 0;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++){
            if(position.get(row, col) == 1) {
                score += getWeightMatrixScore(position, row, col);
            }
            if(position.get(row, col) == -1) {
                score -= getWeightMatrixScore(position, row, col);
            }
        }
    }
    return score;
}

pair<Position, int> Game::alfabeta(Position position, int depth, int alfa, int beta, int maximizing_player) {
    if(depth == 0 || position.noMove()){
        return make_pair(position, this->calculateScore(position));
    }
    int min_player = -maximizing_player;
    if(maximizing_player == 1) {
        pair<Position, int> value = make_pair(position, -INT_MAX);
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++){
                if(position.get(row, col) == 2) {
                    Position newPos(position);
                    newPos.addChip(row, col, maximizing_player);
                    newPos.setAvailable(min_player);
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, -1).second;
                    if(new_value > value.second) {
                        value = make_pair(newPos, new_value);
                    }
                    if(value.second > beta) {
                        break;
                    }
                    alfa = max(alfa, value.second);
                }
            }
        }
        return value;
    }
    else {
        pair<Position, int> value = make_pair(position, INT_MAX);
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(position.get(row, col) == 2) {
                    Position newPos(position);
                    newPos.addChip(row, col, maximizing_player);
                    newPos.setAvailable(min_player);
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, 1).second;
                    if(new_value < value.second) {
                        value = make_pair(newPos, new_value);
                    }
                    if(value.second < alfa) {
                        break;
                    }
                    beta = min(beta, value.second);
                }
            }
        }
        return value;
    }
}

Position Game::getHumanMovement() {
    while(true) {
        int posX, posY;
        getMouse(posX, posY);
        posX = floor((posX - 100)/75);
        posY = floor((posY - 100)/75);
        if(gamePosition.get(posX, posY) == 2) {
            gamePosition.addChip(posX, posY, turn);
            break;
        }
    }
    return gamePosition;
}

void Game::update() {
    if(turn == aiColor) {
        int depth = 5;
        gamePosition = alfabeta(gamePosition, depth, -INT_MAX, INT_MAX, aiColor).first;
    } else {
        gamePosition = getHumanMovement();
    }
    changeTurn();
    if(gamePosition.noMove()) {
        changeTurn();
        if(gamePosition.noMove()) {
            finished = true;
        }
    }
}

void Game::draw() {
    display.drawBoard();
    display.drawChips(gamePosition.getMatrix(), gamePosition.getLastChip());
    display.drawScore(gamePosition.getScoreWhite(), gamePosition.getScoreBlack());
    if(finished) {
        display.drawResults(gamePosition.getScoreWhite(), gamePosition.getScoreBlack());
    }
}


void Game::exit() {
    clearWindow();
    closeWindow(display.getWindow());
}
