#include "Game.h"
#include <ctime>
using namespace std;
int main() {
    srand(time(NULL));
    Game game;

    game.startGame();

    return 0;
}
