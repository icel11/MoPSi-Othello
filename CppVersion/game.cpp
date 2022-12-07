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


int calculateScore(Position position, int color) {
    int score = 0;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++){
            if(position.get(row, col) == 1) {
                score += abs(row-3.5)+abs(col-3.5);
            }
            if(position.get(row, col) == -1) {
                score -= abs(row-3.5)+abs(col-3.5);
            }
        }
    }
    return score * color;

    // Trivial approach:
    // return (position.getScoreBlack() - position.getScoreWhite()) * color;
}


pair<Position, int> Game::calculateMovement(Position position, int color, int depth) {
    if(depth == 0)
        return make_pair(position, calculateScore(position, color));
    else {
        vector<pair<Position, int>> possibleMouvements;
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++){
                if(position.get(row, col) == 2) {
                    Position newPos(position);
                    int auxColor = color;
                    newPos.addChip(row, col, auxColor);
                    possibleMouvements.push_back(make_pair(newPos, calculateMovement(newPos, auxColor, depth - 1).second));
                }
            }
        }
        if(possibleMouvements.empty()) {
            return make_pair(position, calculateScore(position, color));
        }
        pair<Position, int> bestMouvement = make_pair(Position(), INT_MIN);
        for(pair<Position, int> pos : possibleMouvements) {
            if(pos.second > bestMouvement.second)
                bestMouvement = pos;
        }
        return bestMouvement;
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
        gamePosition = calculateMovement(gamePosition, turn, 4).first;
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
