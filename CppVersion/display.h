#pragma once
#include <Imagine/Graphics.h>
#include <vector>

using namespace Imagine;
using namespace std;


/**
 * The Display class manages the visuals of the game.
 */
class Display
{
private:
    Window window;
    const Color GREEN = Color(15, 100, 15);
    const Color GREY = Color(50, 50, 50);
public:
    const int WIDTH = 800;
    const int HEIGHT = 800;
    Display();

    /// Draws the black lines of the board
    void drawBoard();

    /// Draws all the chips. BLACK if it is a 1, WHITE if -1, an void circle if available
    void drawChips(vector<vector<int>> chips);

    /// Calls draw Chips, and adds a small red circle to indicate the last chip placed
    void drawChips(vector<vector<int>> chips, vector<int> lastChip);

    /// Draws the score of both WHITE and BLACK players
    void drawScore(int scoreWhite, int scoreBlack);

    /// Draws the result of the game (who won or if it was a tie)
    void drawResults(int scoreWhite, int scoreBlack);

    /// Draws the settings (the initial menu)
    void drawSettings(int aiColor);

    /// Window getter
    Window getWindow() { return window; };
};
