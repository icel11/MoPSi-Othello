#pragma once
#include "display.h"
#include "position.h"


/**
 * The Game class contains all information regarding the game and its methods to modify it.
 */
class Game
{
private:
    /// Used to show the game
    Display display = Display();

    /// Used to stored the game matrix, acces the methods to modify, and keep extra info (like last position)
    Position gamePosition;

    /**
     * getWeightMatrixScore is used by the AI. It calculates the weight of a piece in a square. It returns the
     * weightMatrix value almost always, the exception is when the row and col are 2 on the -25 squares and
     * the corner is occupied with a piece. It transforms them from -25 and to 2, because they are no longer
     * punitive.
     *
     * @param position: position of the game that we want to analyze (not necessarily the current one if we are
     * in a Nth depth)
     * @param row: row of the square we want to know the weight of
     * @param col: column of the square we want to know the weight of
     * @return The weight of that square
     */
    int getWeightMatrixScore(Position position, int row, int col);

    /**
     * calculateScore is used by the AI to estimate the value given a position. It scales the weights to the pieces,
     * so if it is very positive BLACK is winning and if it is very negative WHITE is winning.
     * @param position: Position for what we want to calculate the value
     * @return The score of a certain position
     */
    int calculateScore(Position position);

    /**
     * alpha-beta-pruning adapted from the wikipedia page's pseudocode:
     * https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning#:~:text=Alpha%E2%80%93beta%20pruning%20is%20a,Connect%204%2C%20etc.)
     * As we don't work with a fixed tree, we calculate the next nodes on each iteration, that's the reason why we
     * not only return the score, but also the position.
     * @return The next position (would represent the children node studied) and its score
     */
    pair<Position, int> alfabeta(Position position, int depth, int alfa, int beta, int maximizing_player);

    /**
     * getHumanMovement takes the user input to place its piece and update the board accordingly
     * @return the new position
     */
    Position getHumanMovement();

    /// If the game is finished
    bool finished = false;

    /// 1 if the AI plays with BLACK, -1 if it plays with WHITE, 0 if it does not play
    int aiColor = 0;

    /// 1 if it is BLACK's turn, -1 if it is WHITE's turn
    int turn = 1;

    /// matrix that will be used to scale the importance of every square
    int weightMatrix[8][8] = {{100,-25, 10,  5,  5, 10,-25, 100},
                              {-25,-25,  2,  2,  2,  2,-25, -25},
                              { 10,  2,  5,  1,  1,  5,  2,  10},
                              {  5,  2,  1,  2,  2,  1,  2,   5},
                              {  5,  2,  1,  2,  2,  1,  2,   5},
                              { 10,  2,  5,  1,  1,  5,  2,  10},
                              {-25,-25,  2,  2,  2,  2,-25, -25},
                              {100,-25, 10,  5,  5, 10,-25, 100}};

    /// Changes the turn and updates the available squares
    void changeTurn();
public:
    /// Constructor. It will take the AI color selected
    Game(int aiColor);

    /// Update will take the AI or human action and change the turn or finish the game if expected
    void update();

    /// Will use the display to show the current state of the game
    void draw();

    /// Will close the game
    void exit();

    /// finished getter
    bool isFinished() { return finished; };
};

