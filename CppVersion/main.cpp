#include <iostream>
#include "game.h"

using namespace Imagine;
using namespace std;




int main()
{
    Game game = Game();
    while(true) {
        int posX, posY;
        getMouse(posX, posY);
        game.update(posX, posY);
        game.draw();
    }
    game.exit();
    return 0;
}
