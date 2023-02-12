#pragma once
#include <vector>

using namespace std;

/**
 * The Position class contains all information of a game position (plus scores and last piece placed)
 */
class Position
{
private:
    /// All available directions vector
    static inline vector<vector<int>> DIRECTIONS = {{0,1}, {-1,1}, {-1,0}, {-1,-1},
                                                    {0,-1},{1,-1}, {1,0}, {1,1}};

    /// Matrix with the chips (1 BLACK, -1 WHITE, 2 AVAILABLE, 0 Empty)
    vector<vector<int>> matrix;

    ///Position of the last chip placed
    vector<int> lastChip = {-100,-100};

    /// Score of the BLACK player
    int scoreBlack = 0;

    /// Score of the WHITE player
    int scoreWhite = 0;

    /// Sets the value of a position and updates the scores. The score update
    /// will depend on turned
    void set(int x, int y, int color, bool turned = false);
public:
    Position();
    Position(vector<vector<int>> position, int turn);

    /// Adds a chip and updates the values of the matrix accordingly (without the
    /// available squares, i.e. the 2's)
    void addChip(int x, int y, int color);

    /// Set the available squares for player 'turn' (i.e. puts the 2's in the matrix)
    void setAvailable(int turn);

    /// gets the value of a position of the matrix
    int get(int x, int y) const;

    /// Checks if there is any square available.
    bool noMove() const;

    vector<vector<int>> getMatrix() { return matrix; };
    vector<int> getLastChip() { return lastChip; };
    int getScoreBlack() { return scoreBlack; };
    int getScoreWhite() { return scoreWhite; };

    /// Prints the matrix on the console
    void print() const;
};
