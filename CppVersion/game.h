#pragma once
#include "display.h"
#include "position.h"
#include "strategies.h"

class Game
{
private:
    Display display = Display();
    Position gamePosition;
    int calculateScore(Position position, int strategy);
    pair<Position, int> alfabeta(Position position, int depth, int alfa, int beta, int maximizing_player, int strategy=1);
    Position getHumanMovement();
    bool finished = false;
    int aiDepth = 2;
    int strategyAI1, strategyAI2;
    int colorAI1 = 1;
    int turn = 1;
    int totalChips = 0;
    Strategies strategies;
    void changeTurn();
public:
    Game(int colorAI1, int strategyAI1, int strategyAI2, int aiDepth);
    void update();
    void draw();
    void reset();
    void exit();
    void logResults();
    bool isFinished() { return finished; };
    int getWinner();
};

