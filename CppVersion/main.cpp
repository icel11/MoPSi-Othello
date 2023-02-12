#include <iostream>
#include "settings.h"
#include "game.h"

using namespace Imagine;
using namespace std;



Game getGame(Settings settings) {
    while(!settings.isReady()) {
        int posX, posY;
        getMouse(posX, posY);
        settings.update(posX, posY);
        settings.draw();
    }
    return Game(settings.getAiColor());
}

void playGame(Game game) {
    while(!game.isFinished()) {
        game.update();
        game.draw();
    }
}

/**
 * main will loop indefinitely through the setting and game. Any click after the game is finished will
 * restart the window and go to the settings menu again.
 */
int main()
{
    while(true) {
        Settings settings = Settings();
        Game game = getGame(settings);
        playGame(game);
        int m;
        getMouse(m, m);
        game.exit();
    }
    return 0;
}
