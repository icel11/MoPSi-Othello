#pragma once
#include "display.h"
#include "position.h"

class Game
{
private:
    Display display = Display();
    Position gamePosition;
    int getWeightMatrixScore(Position position, int row, int col);
    int calculateScore(Position position);
    pair<Position, int> alfabeta(Position position, int depth, int alfa, int beta, int maximizing_player);
    Position getHumanMovement();
    bool finished = false;
    int aiColor = 0;
    int turn = 1;
    int weightMatrix[8][8] = {{100,-25, 10,  5,  5, 10,-25, 100},
                              {-25,-25,  2,  2,  2,  2,-25, -25},
                              { 10,  2,  5,  1,  1,  5,  2,  10},
                              {  5,  2,  1,  2,  2,  1,  2,   5},
                              {  5,  2,  1,  2,  2,  1,  2,   5},
                              { 10,  2,  5,  1,  1,  5,  2,  10},
                              {-25,-25,  2,  2,  2,  2,-25, -25},
                              {100,-25, 10,  5,  5, 10,-25, 100}};

    void changeTurn();
public:
    Game(int aiColor);
    void update();
    void draw();
    void reset();
    void exit();
    bool isFinished() { return finished; };
};

