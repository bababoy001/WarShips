#include "Game.h"
#include <ctime>

int main() {
    srand(time(NULL));
    Game game;

    game.startGame();

    return 0;
}
