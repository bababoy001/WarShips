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
    printAll.placeShip(random);
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
    myShips.createFleet(map, random, height, length);
    enemyShips.createFleet(enemyMap, 1, height, length);
    pair<int, int> pairForMiss = make_pair(-1, -1);
    while (!gameEnded) {
        if (playerTurn) {
            printAll.printAllMaps(map, enemyMap, height, length);
            pair<int, int> pairXY = attackPlayer(enemyMap, height, length);
            if (pairXY != pairForMiss) {
                if (myShips.isMine(pairXY, map, height, length, enemyShips, zalp, myShips, hitedBoards)) {
                    mines.push_back(pairXY);
                }
                else {
                    myShips.checkShipInHit(pairXY, enemyMap, height, length, enemyShips, zalp, hitedBoards);
                }
            }
            else if (zalpNum) {
                printAll.printSentence("The enemy destroys your main ship, you can fire back");
                playerTurn = !playerTurn;
                zalpNum--;
            }
            if (zalp) {
                printAll.printSentence("You destroy the enemy's capital ship, the enemy will fire a salvo in response");
                playerTurn = !playerTurn;
                zalpNum = 2;
                zalp = 0;
            }
        }
        else {
            if (!hitedBoards.empty()){
                pairHitedBoards = hitedBoards[0];
                hitedBoards.erase(hitedBoards.begin());
            }

            pair<int, int> pairXY = bot->attack(playerTurn, map, height, length, myShips.countReadyShip, mines, pairHitedBoards);
            if (pairXY != pairForMiss) {
                if (enemyShips.isMine(pairXY, enemyMap, height, length, myShips, zalp, enemyShips, hitedBoards)) {

                }
                else {
                    enemyShips.checkShipInHit(pairXY, map, height, length, myShips, zalp, hitedBoards);
                }
                
            }
            else if (zalpNum) {
                printAll.printSentence("You destroy the enemy's capital ship, the enemy will fire a salvo in response");
                playerTurn = !playerTurn;
                zalpNum--;
            }
            if (zalp) {
                printAll.printSentence("The enemy destroys your main ship, you can fire back");
                playerTurn = !playerTurn;
                zalpNum = 2;
                zalp = 0;
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
    if (currentMap[x][y].isHit || currentMap[x][y].isMiss || currentMap[x][y].isHitFromMine) {
        printAll.printSentence("This cell already hitted");
        return attackPlayer(currentMap, height, length);
    }

    if (currentMap[x][y].isMine) {
        currentMap[x][y].isHit = 1;
        playerTurn = !playerTurn;
        return make_pair(x, y);
    }
    else if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
        currentMap[x][y].isMiss = 1;
        playerTurn = !playerTurn;
        return make_pair(-1, -1);
    }
    else if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
        currentMap[x][y].isHit = 1;
        return make_pair(x, y);
    }
}
