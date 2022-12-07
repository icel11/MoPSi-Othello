#pragma once
#include "display.h"
#include "position.h"

class Game
{
private:
    Display display = Display();
    Position gamePosition;
    pair<Position, int> calculateMovement(Position position, int color, int depth);
    Position getHumanMovement();
    bool finished = false;
    int aiColor = 0;
    int turn = 1;
    void changeTurn();
public:
    Game(int aiColor);
    void update();
    void draw();
    void reset();
    void exit();
    bool isFinished() { return finished; };
};

