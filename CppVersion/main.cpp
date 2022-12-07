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
