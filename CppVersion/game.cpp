#include "game.h"
#include <map>

Game::Game()
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
    draw();
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
        pair<Position, int> bestMouvement = make_pair(Position(), -64);
        for(pair<Position, int> pos : possibleMouvements) {
            if(pos.second > bestMouvement.second)
                bestMouvement = pos;
        }
        return bestMouvement;
    }
}

void Game::update(int posX, int posY) {
    if(posX > 100 && posY > 100) {
        int squareX = floor((posX - 100) / 75);
        int squareY = floor((posY - 100) / 75);
        if(gamePosition.get(squareX, squareY) == 2) {
            int auxTurn = turn;
            finished = gamePosition.addChip(squareX, squareY, turn);
            if(!finished && turn != auxTurn){
                draw();
                int m = 0;
                gamePosition = calculateMovement(gamePosition, turn, 4).first;
                turn *= -1;
                finished = gamePosition.noMove();
            }
        }
    }
}

void Game::draw() {
    display.drawBoard();
    display.drawChips(gamePosition.getMatrix());
    display.drawScore(gamePosition.getScoreWhite(), gamePosition.getScoreBlack());
    if(finished) {
        display.drawResults(gamePosition.getScoreWhite(), gamePosition.getScoreBlack());
    }
}


void Game::exit() {
    clearWindow();
    closeWindow(display.getWindow());
}
