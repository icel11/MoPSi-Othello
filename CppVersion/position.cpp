#include "position.h"
#include <iomanip>
#include <iostream>

using namespace std;

Position::Position() {}

Position::Position(vector<vector<int>> position, int turn)
{
    this->matrix = position;
    for(int row = 0; row < 8; row++)
        for(int col = 0; col < 8; col++){
            if(matrix[row][col] == -1)
                scoreWhite++;
            if(matrix[row][col] == 1)
                scoreBlack++;
        }
    setAvailable(turn);
}


void Position::set(int x, int y, int color, bool turned) {
    if(color == 1)
        scoreBlack++;
    if(color == -1)
        scoreWhite++;
    if(turned) {
        if(color == 1)
            scoreWhite--;
        if(color == -1)
            scoreBlack--;
    }
    matrix[x][y] = color;
}

int Position::get(int x, int y) const {
    if(x < 8 && x >= 0 && y < 8 && y >= 0) {
        return matrix[x][y];
    }
    return 0;
}

void Position::setAvailable(int color) {
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(get(row, col) == 2){
                matrix[row][col] = 0;
            }
            if(get(row, col) == 0){
                for(vector<int> direction : DIRECTIONS){
                    int posX = row + direction[0];
                    int posY = col + direction[1];
                    while(get(posX, posY) == -color){
                        posX += direction[0];
                        posY += direction[1];
                        if(get(posX, posY) == color) {
                            matrix[row][col] = 2;
                        }
                    }
                }
            }
        }
    }
}

void Position::addChip(int posX_0, int posY_0, int color) {
    set(posX_0, posY_0, color);
    lastChip = {posX_0, posY_0};
    for(vector<int> direction : DIRECTIONS){
        int posX = posX_0 + direction[0];
        int posY = posY_0 + direction[1];
        if(get(posX, posY) == -color) {
            posX += direction[0];
            posY += direction[1];
            while(get(posX, posY) == -color){
                posX += direction[0];
                posY += direction[1];
            }
            if(get(posX, posY) == color) {
                while(posX != posX_0 || posY != posY_0) {
                    if(get(posX, posY) != color) {
                        set(posX, posY, color, true);
                    }
                    posX -= direction[0];
                    posY -= direction[1];
                }
            }
        }
    }
}

bool Position::noMove() const {
    for(int row = 0; row < 8; row++)
        for(int col = 0; col < 8; col++)
            if(matrix[row][col] == 2)
                return false;
    return true;
}

void Position::print() const {
    std::cout<<endl;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            cout << setw(3) << get(col, row);
        }
        cout << endl;
    }
}
