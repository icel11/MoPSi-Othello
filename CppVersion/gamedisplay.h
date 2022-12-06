#pragma once
#include <Imagine/Graphics.h>
#include <vector>

using namespace Imagine;
using namespace std;

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
    void drawBoard();
    void drawChips(vector<vector<int>> chips);
    void drawScore(int scoreWhite, int scoreBlack);
    void drawResults(int scoreWhite, int scoreBlack);
    void drawSettings(bool multiPlayer, bool color);
    Window getWindow() { return window; };
};
