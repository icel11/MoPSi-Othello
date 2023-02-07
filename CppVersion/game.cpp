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

int Game::calculateScore(Position position, int color) {
    int score = 0;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++){
            score += weightMatrix[row][col] * position.get(row, col);
        }
    }
    return score * (-1);
}


int calculateScore(Position position, int color) {
    int score = 0;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++){
            if(position.get(row, col) == 1) {
                score += pow(abs(row-3.5)+abs(col-3.5), 2);
            }
            if(position.get(row, col) == -1) {
                score -= pow(abs(row-3.5)+abs(col-3.5), 2);
            }
        }
    }
    return score * color;

    // Trivial approach:
    // return (position.getScoreBlack() - position.getScoreWhite()) * color;
}


pair<Position, int> Game::alfabeta(Position position, int depth, int alfa, int beta, int turn, bool maximizing_player) {
    if(depth == 0 || position.noMove())
        return make_pair(position, this->calculateScore(position, turn));
    if(maximizing_player) {
        pair<Position, int> value = make_pair(position, -INT_MAX);
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++){
                if(position.get(row, col) == 2) {
                    Position newPos(position);
                    int auxTurn = turn;
                    newPos.addChip(row, col, auxTurn);
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, auxTurn, false).second;
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
            for(int col = 0; col < 8; col++){
                if(position.get(row, col) == 2) {
                    Position newPos(position);
                    int auxTurn = turn;
                    newPos.addChip(row, col, auxTurn);
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, auxTurn, true).second;
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
        gamePosition = alfabeta(gamePosition, 3, -INT_MAX, INT_MAX, turn, true).first;
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
