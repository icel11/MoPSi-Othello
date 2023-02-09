#pragma once
#include "position.h"

class Strategies
{
public:
    Strategies();
    int getWeightMatrixScore(int strategy, Position position, int row, int col, int totalChips);
    static int getWeightMatrixScore1(Position position, int row, int col, int totalChips);
    static int getWeightMatrixScore2(Position position, int row, int col, int totalChips);
    static int getWeightMatrixScore3(Position position, int row, int col, int totalChips);
    static int getWeightMatrixScore4(Position position, int row, int col, int totalChips);
    static int getWeightMatrixScore5(Position position, int row, int col, int totalChips);
};

