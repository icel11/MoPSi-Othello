#include "strategies.h"
#include <cmath>
#include <iostream>

using namespace std;

Strategies::Strategies() {}

int WEIGHT_MATRIX_1[8][8] = {{100,-25, 10,  5,  5, 10,-25, 100},
                          {-25,-25,  2,  2,  2,  2,-25, -25},
                          { 10,  2,  5,  1,  1,  5,  2,  10},
                          {  5,  2,  1,  2,  2,  1,  2,   5},
                          {  5,  2,  1,  2,  2,  1,  2,   5},
                          { 10,  2,  5,  1,  1,  5,  2,  10},
                          {-25,-25,  2,  2,  2,  2,-25, -25},
                          {100,-25, 10,  5,  5, 10,-25, 100}};

int WEIGHT_MATRIX_2[8][8] = {{100,-100, 10,  5,  5, 10,-100, 100},
                          {-100,-100,  2,  2,  2,  2,-100, -100},
                          { 10,  2,  5,  1,  1,  5,  2,  10},
                          {  5,  2,  1,  2,  2,  1,  2,   5},
                          {  5,  2,  1,  2,  2,  1,  2,   5},
                          { 10,  2,  5,  1,  1,  5,  2,  10},
                          {-100,-100,  2,  2,  2,  2,-100, -100},
                          {100,-100, 10,  5,  5, 10,-100, 100}};

int Strategies::getWeightMatrixScore(int strategy, Position position, int row, int col, int totalChips) {
    switch(strategy) {
        case 1:
            return getWeightMatrixScore1(position, row, col, totalChips);
        case 2:
            return getWeightMatrixScore2(position, row, col, totalChips);
        case 3:
            return getWeightMatrixScore3(position, row, col, totalChips);
        case 4:
            return getWeightMatrixScore4(position, row, col, totalChips);
        case 5:
            return getWeightMatrixScore5(position, row, col, totalChips);
        default:
            return getWeightMatrixScore1(position, row, col, totalChips);
    };
}

int Strategies::getWeightMatrixScore1(Position position, int row, int col, int totalChips) {
    return 1;
}

int Strategies::getWeightMatrixScore2(Position position, int row, int col, int totalChips) {
    return abs(4 - row) + abs(4 - col);
}

int Strategies::getWeightMatrixScore3(Position position, int row, int col, int totalChips) {
    return WEIGHT_MATRIX_1[row][col];
}

int Strategies::getWeightMatrixScore4(Position position, int row, int col, int totalChips) {
    if(((row == 1 and col == 0) or (row == 0 and col == 1) or (row == 1 and col == 1)) and abs(position.get(0,0)) == 1) {
        return 2;
    }
    if(((row == 0 and col == 6) or (row == 1 and col == 6) or (row == 1 and col == 7)) and abs(position.get(0,7)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 0) or (row == 6 and col == 1) or (row == 7 and col == 1)) and abs(position.get(7,0)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 7) or (row == 7 and col == 6) or (row == 6 and col == 6)) and abs(position.get(7,7)) == 1) {
        return 2;
    }
    return WEIGHT_MATRIX_2[row][col];
}

int Strategies::getWeightMatrixScore5(Position position, int row, int col, int totalChips) {
    if(((row == 1 and col == 0) or (row == 0 and col == 1) or (row == 1 and col == 1)) and abs(position.get(0,0)) == 1) {
        return 2;
    }
    if(((row == 0 and col == 6) or (row == 1 and col == 6) or (row == 1 and col == 7)) and abs(position.get(0,7)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 0) or (row == 6 and col == 1) or (row == 7 and col == 1)) and abs(position.get(7,0)) == 1) {
        return 2;
    }
    if(((row == 6 and col == 7) or (row == 7 and col == 6) or (row == 6 and col == 6)) and abs(position.get(7,7)) == 1) {
        return 2;
    }
    if(totalChips > 50)
        return 1;
    return WEIGHT_MATRIX_2[row][col];
}

