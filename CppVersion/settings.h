#pragma once
#include "display.h"

using namespace Imagine;


/**
 * The Settings class manages the initial menu
 */
class Settings
{
private:
    Display display;
    bool gameReady = false;
    int aiColor = 0;
public:
    Settings();

    /// Grabs the user input to update the setting
    void update(int posX, int posY);

    /// Draws the game settings
    void draw();

    bool isReady() { return gameReady; };
    int getAiColor() { return aiColor; };
};
