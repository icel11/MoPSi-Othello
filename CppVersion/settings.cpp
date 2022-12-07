#include "settings.h"
#include <math.h>

Settings::Settings()
{
    display.drawSettings(aiColor);
}


bool collidesCircle(int posX, int posY, int circleX, int circleY, int r) {
    return pow(posX - circleX, 2) + pow(posY - circleY, 2) < pow(r, 2);
}


void Settings::update(int posX, int posY) {
    if(collidesCircle(posX, posY, display.WIDTH/2 - 100, display.HEIGHT/2 - 100, 25))
        aiColor = -1;
    if(collidesCircle(posX, posY, display.WIDTH/2, display.HEIGHT/2 - 100, 25))
        aiColor = 0;
    if(collidesCircle(posX, posY, display.WIDTH/2 + 100, display.HEIGHT/2 - 100, 25))
        aiColor = 1;
    if(posY > display.HEIGHT*2/3 && posY < display.HEIGHT*2/3 + 100 && posX > display.WIDTH/3 && posX < display.WIDTH*2/3) {
        gameReady = true;
        clearWindow();
        closeWindow(display.getWindow());
    }
}

void Settings::draw() {
    display.drawSettings(aiColor);
}
