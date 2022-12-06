#pragma once
#include <vector>

using namespace std;

class Position
{
private:
    static inline vector<vector<int>> DIRECTIONS = {{0,1}, {-1,1}, {-1,0}, {-1,-1},
                                                    {0,-1},{1,-1}, {1,0}, {1,1}};
    vector<vector<int>> matrix;
    int scoreBlack = 0;
    int scoreWhite = 0;
    void set(int x, int y, int color, bool turned = false);
    void setAvailable(int turn);
public:
    Position();
    Position(vector<vector<int>> position, int turn);
    bool addChip(int x, int y, int &color);
    int get(int x, int y) const;
    bool noMove() const;
    vector<vector<int>> getMatrix() { return matrix; };
    int getScoreBlack() { return scoreBlack; };
    int getScoreWhite() { return scoreWhite; };
};
