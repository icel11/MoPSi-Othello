#pragma once
#include "gamedisplay.h"
#include "position.h"

class Game
{
private:
    Display display = Display();
    Position gamePosition;
    pair<Position, int> calculateMovement(Position position, int color, int depth);
    bool finished = false;
    int turn = 1;
public:
    Game();
    void update(int x, int y);
    void draw();
    void reset();
    void exit();
    bool isFinished() { return finished; };
};

