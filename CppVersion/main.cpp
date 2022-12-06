#include <iostream>
#include "settings.h"
#include "game.h"

using namespace Imagine;
using namespace std;



Game getGame() {
    Settings settings = Settings();
    while(!settings.isReady()) {
        int posX, posY;
        getMouse(posX, posY);
        settings.update(posX, posY);
        settings.draw();
    }
    return Game();
}

int main()
{
    while(true) {
        Game game = getGame();
        while(!game.isFinished()) {
            int posX, posY;
            getMouse(posX, posY);
            game.update(posX, posY);
            game.draw();
        }
        int m;
        getMouse(m, m);
        game.exit();
    }
    return 0;
}
