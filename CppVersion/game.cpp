#include "game.h"
#include <map>
#include <limits.h>
#include <ctime>
#include <iomanip>

Game::Game(int colorAI1, int startegyAI1, int strategyAI2, int aiDepth)
{
    this->strategyAI1 = strategyAI1;
    this->strategyAI2 = strategyAI2;
    this->aiDepth = aiDepth;
    reset();
    this-> colorAI1 = colorAI1;
    draw();
}

void Game::reset() {
    totalChips = 0;
    turn = 1;
    finished = false;
    srand(time(0));
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
}

void Game::changeTurn() {
    turn *= -1;
    gamePosition.setAvailable(turn);
}

int Game::calculateScore(Position position, int strategy) {
    int score = 0;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++){
            if(position.get(row, col) == 1) {
                score += strategies.getWeightMatrixScore(strategy, position, row, col, totalChips);
            }
            if(position.get(row, col) == -1) {
                score -= strategies.getWeightMatrixScore(strategy, position, row, col, totalChips);
            }
        }
    }
    return score;
}

pair<Position, int> Game::alfabeta(Position position, int depth, int alfa, int beta, int maximizing_player, int strategy) {
    //cout << "Depth:" << depth << endl;
    //cout << "Maximizing player: " << maximizing_player << endl;
    //cout << "Score: " << this->calculateScore(position) << endl;
    //position.print();
    if(depth == 0 || position.noMove()){
        return make_pair(position, this->calculateScore(position, strategy));
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
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, -1, strategy).second;
                    if(new_value >= value.second) {
                        if(new_value == value.second) {
                            if(rand() % 2 == 0)
                                value = make_pair(newPos, new_value);
                        } else {
                            value = make_pair(newPos, new_value);
                        }
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
                    int new_value = alfabeta(newPos, depth-1, alfa, beta, 1, strategy).second;
                    if(new_value < value.second) {
                        if(new_value == value.second) {
                            if(rand() % 2 == 0)
                                value = make_pair(newPos, new_value);
                        } else {
                            value = make_pair(newPos, new_value);
                        }
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
    totalChips++;
    if(turn == colorAI1) {
        gamePosition = alfabeta(gamePosition, aiDepth, -INT_MAX, INT_MAX, turn, strategyAI1).first;
    } else {
        gamePosition = alfabeta(gamePosition, aiDepth, -INT_MAX, INT_MAX, turn, strategyAI2).first;
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

void Game::logResults() {
    cout << "Game result: ";
    if(getWinner() == 1)
        cout << "black won";
    if(getWinner() == -1)
        cout << "white won";
    if(getWinner() == 0)
        cout << "draw";
    cout << " " << colorAI1 << " has the first strategy" << endl;
}

int Game::getWinner() {
    if(gamePosition.getScoreBlack() > gamePosition.getScoreWhite())
        return 1;
    if(gamePosition.getScoreBlack() < gamePosition.getScoreWhite())
        return -1;
    return 0;
}

