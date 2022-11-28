#pragma once
#include <Imagine/Graphics.h>
#include <vector>

using namespace Imagine;
using namespace std;

class GameDisplay
{
private:
    Window window;
    const int WIDTH = 800;
    const int HEIGHT = 800;
    const Color GREEN = Color(15, 100, 15);
    const Color WHITE = Color(255, 255, 255);
    const Color BLACK = Color(0, 0, 0);
public:
    GameDisplay();
    void drawBoard();
    void drawChips(vector<vector<int>> chips);
    void drawScore(int scoreWhite, int scoreBlack);
    void drawResults(int scoreWhite, int scoreBlack);
    Window getWindow() { return window; };
};
