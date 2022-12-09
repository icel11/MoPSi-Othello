#pragma once
#include "display.h"

using namespace Imagine;

class Settings
{
private:
    Display display;
    bool gameReady = false;
    int aiColor = 0;
public:
    Settings();
    void update(int posX, int posY);
    void draw();
    bool isReady() { return gameReady; };
    int getAiColor() { return aiColor; };
};
