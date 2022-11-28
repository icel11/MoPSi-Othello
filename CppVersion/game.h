#pragma once
#include "gamedisplay.h"

class Game
{
private:
    GameDisplay display = GameDisplay();
    vector<vector<int>> chips;
    const vector<vector<int>> DIRECTIONS = {{0,1}, {-1,1}, {-1,0}, {-1,-1},
                                            {0,-1}, {1,-1}, {1,0}, {1,1}};
    bool finished = false;
    int scoreWhite = 0;
    int scoreBlack = 0;
    int turn = 1;
    void putChip(int x, int y, int color, bool turned = false);
    int getChip(int x, int y);
    void setAvailable(int turn);
    void addChip(int x, int y, int color);
    bool noMove();
public:
    Game();
    void update(int x, int y);
    void draw();
    void reset();
    void exit();
};

