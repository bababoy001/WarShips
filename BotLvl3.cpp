#include "BotLvl3.h"
#include <cstdlib>
using namespace std;
BotLvl3::BotLvl3() : firstHit(-1, -1), lastHit(-1, -1), destroying(false), directionIndex(0), foundDirection(false), attempt(0), lastPlayerShips(0) {}

pair<int, int> BotLvl3::attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips, vector<pair<int, int>>& mines) {
    int x, y;
    if (currntPlayerShips < lastPlayerShips) {
        attempt = 0;
        destroying = 0;
        foundDirection = 0;
    }
    lastPlayerShips = currntPlayerShips;

    if (!mines.empty() && !destroying) {
        firstHit = mines[0];
        lastHit = mines[0];
        destroying = 1;
        mines.erase(mines.begin());
    }

    botShoot(currentMap, height, length, x, y);

    if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
        printAll.printSentence("This cell already hitted");
        return attack(playerTurn, currentMap, height, length, currntPlayerShips, mines);
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
        if (!destroying) {
            firstHit = make_pair(x, y);
            lastHit = make_pair(x, y);
            destroying = 1;
        }
        return make_pair(x, y);
    }
}

void BotLvl3::botShoot(vector<vector<Cell>>& currentMap, int height, int length, int& x, int& y) {
    if (!destroying) {
        //x = rand() % height;            //розкоментувати після перевірки
        //y = rand() % length;
        printAll.cinCoord(x, y);      //видалити після перевірок


    }
    else {
        findNextTarget(currentMap, x, y, height, length);
    }
}

void BotLvl3::findNextTarget(vector<vector<Cell>>& currentMap, int& x, int& y, int height, int length) {
    if (attempt >= 4) {
        printAll.printSentence("attempt attempt");  //перевірка
        attempt = 0;
        destroying = 0;
        foundDirection = 0;
        return botShoot(currentMap, height, length, x, y);
    }

    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    int dx = directions[directionIndex].first;
    int dy = directions[directionIndex].second;
    int newX = lastHit.first + dx;
    int newY = lastHit.second + dy;

    if (!check.isCellInMap(newX, newY, height, length)) {
        if (foundDirection) {
            lastHit = firstHit;
            reverseDirection();
        }
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
        }
        return findNextTarget(currentMap, x, y, height, length);
    }

    if (check.isCellInMap(newX, newY, height, length) && !currentMap[newX][newY].isHit && !currentMap[newX][newY].isMiss && !currentMap[newX][newY].isShip) {
        if (foundDirection) {
            x = newX;
            y = newY;
            lastHit = firstHit;
            reverseDirection();
        }
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
            x = newX;
            y = newY;
            return;
        }
    }
    else if (check.isCellInMap(newX, newY, height, length) && currentMap[newX][newY].isMiss) {
        lastHit = firstHit;
        if (foundDirection) {
            reverseDirection();
            findNextTarget(currentMap, x, y, height, length);
        }
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
            findNextTarget(currentMap, x, y, height, length);
        }
    }
    else if (!currentMap[newX][newY].isHit && currentMap[newX][newY].isShip) {
        x = newX;
        y = newY;
        lastHit = make_pair(x, y);
        foundDirection = 1;
    }
    else if (currentMap[newX][newY].isHitFromMine && currentMap[newX][newY].isShip) {
        lastHit = make_pair(newX, newY);
        foundDirection = 1;
        findNextTarget(currentMap, x, y, height, length);
    }
    else {
        directionIndex = (directionIndex + 1) % 4;
        attempt++;
        findNextTarget(currentMap, x, y, height, length);
    }
}

void BotLvl3::reverseDirection() {
    if (directionIndex == 0) directionIndex = 1;
    else if (directionIndex == 1) directionIndex = 0;
    else if (directionIndex == 2) directionIndex = 3;
    else if (directionIndex == 3) directionIndex = 2;
}
