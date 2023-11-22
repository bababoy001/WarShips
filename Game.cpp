#include "Game.h"
using namespace std;
Game::Game() : height(10), length(10), lvlBot(0), gameEnded(false), playerTurn(true), bot(nullptr) {}

Game::~Game() {
    delete bot;
}

vector<vector<Cell>> Game::createMap() {
    return vector<vector<Cell>>(height, vector<Cell>(length));
}

void Game::enterSettings() {
    printAll.sizeMap(height, length);
    printAll.lvlChoice(lvlBot);
    switch (lvlBot) {
    case 1:
        bot = new BotLvl1();
        break;
    case 2:
        bot = new BotLvl2();
        break;
    case 3:
        bot = new BotLvl3();
        break;
    default:
        printAll.printSentence("Invalid level. Setting to level 1");
        bot = new BotLvl1();
        break;
    }
}

void Game::startGame() {
    enterSettings();
    map = createMap();
    enemyMap = createMap();
    myShips.createFleet(map, 0, height, length);
    enemyShips.createFleet(enemyMap, 1, height, length);
    pair<int, int> pairForMiss = make_pair(-1, -1);
    while (!gameEnded) {
        if (playerTurn) {
            printAll.printAllMaps(map, enemyMap, height, length);
            pair<int, int> pairXY = attackPlayer(enemyMap, height, length);
            if (pairXY != pairForMiss) {
                myShips.checkShipInHit(pairXY, enemyMap, height, length, enemyShips);
            }
        }
        else {
            pair<int, int> pairXY = bot->attack(playerTurn, map, height, length, myShips.countReadyShip);
            if (pairXY != pairForMiss) {
                enemyShips.checkShipInHit(pairXY, map, height, length, myShips);
            }
        }

        if (enemyShips.countReadyShip == 0) {
            printAll.printAllMaps(map, enemyMap, height, length);
            printAll.printSentence("Congratulations! You've destroyed all enemy ships. You win!");
            gameEnded = true;
        }

        if (myShips.countReadyShip == 0) {
            printAll.printAllMaps(map, enemyMap, height, length);
            printAll.printSentence("Game over! All your ships have been destroyed. You lose.");
            gameEnded = true;
        }
    }
}

pair<int, int> Game::attackPlayer(vector<vector<Cell>>& currentMap, int height, int length) {
    int x, y;

    printAll.printSentence("Enter coordinates (number letter): ");
    
    printAll.cinCoord(x, y);

    if (!check.isCellInMap(x, y, height, length)) {
        printAll.printSentence("Wrong coordinates");
        return attackPlayer(currentMap, height, length);
    }
    if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
        printAll.printSentence("This cell already hitted");
        return attackPlayer(currentMap, height, length);
    }
    if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
        currentMap[x][y].isMiss = 1;
        playerTurn = !playerTurn;
        return std::make_pair(-1, -1);
    }
    if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
        currentMap[x][y].isHit = 1;
        return std::make_pair(x, y);
    }
}
