#pragma once
#include <vector>

using namespace std;

class Position
{
private:
    static inline vector<vector<int>> DIRECTIONS = {{0,1}, {-1,1}, {-1,0}, {-1,-1},
                                                    {0,-1},{1,-1}, {1,0}, {1,1}};
    vector<vector<int>> matrix;
    vector<int> lastChip = {-100,-100};
    int scoreBlack = 0;
    int scoreWhite = 0;
    void set(int x, int y, int color, bool turned = false);
public:
    Position();
    Position(vector<vector<int>> position, int turn);
    void addChip(int x, int y, int &color);
    void setAvailable(int turn);
    int get(int x, int y) const;
    bool noMove() const;
    vector<vector<int>> getMatrix() { return matrix; };
    vector<int> getLastChip() { return lastChip; };
    int getScoreBlack() { return scoreBlack; };
    int getScoreWhite() { return scoreWhite; };
};
