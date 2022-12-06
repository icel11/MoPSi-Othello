#pragma once
#include "gamedisplay.h"

using namespace Imagine;

class Settings
{
private:
    Display display;
    bool gameReady = false;
    bool multiPlayer = false;
    bool isWhite = false;
public:
    Settings();
    void update(int posX, int posY);
    void draw();
    bool isReady() { return gameReady; };
};
