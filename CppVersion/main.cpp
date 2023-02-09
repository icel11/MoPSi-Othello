#include <iostream>
#include "settings.h"
#include "game.h"
#include <iomanip>

using namespace Imagine;
using namespace std;

int STRATEGY_AI_1 = 1;
int STRATEGY_AI_2 = 4;
int AI_DEPTH = 2;
int GAMES_PER_ROUND = 100;

Game getGame(Settings settings) {
    while(!settings.isReady()) {
        int posX, posY;
        getMouse(posX, posY);
        settings.update(posX, posY);
        settings.draw();
    }
    return Game(settings.getAiColor(), STRATEGY_AI_1, STRATEGY_AI_2, AI_DEPTH);
}

void playGame(Game game) {
    int blackWins = 0;
    int draws = 0;
    int whiteWins = 0;
    for(int i = 0; i < GAMES_PER_ROUND; i++) {
        while(!game.isFinished()) {
            game.update();
            game.draw();
        }
        game.logResults();
        if(game.getWinner() == 1)
            blackWins++;
        if(game.getWinner() == -1)
            whiteWins++;
        if(game.getWinner() == 0)
            draws++;
        game.reset();
    }
    cout << endl;
    cout << setprecision(2) << "B: " << (float)blackWins/GAMES_PER_ROUND;
    cout << " W: " << (float) whiteWins/GAMES_PER_ROUND;
    cout << " D: " << (float) draws/GAMES_PER_ROUND << endl;
    cout << endl;
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
