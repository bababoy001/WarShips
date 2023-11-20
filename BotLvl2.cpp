#include "BotLvl2.h"
#include <cstdlib>

BotLvl2::BotLvl2() : firstHit(-1, -1), lastHit(-1, -1), destroying(false), directionIndex(0), foundDirection(false), attempt(0), lastPlayerShips(0) {}

std::pair<int, int> BotLvl2::attack(bool& playerTurn, std::vector<std::vector<Cell>>& currentMap, int height, int length, int currntPlayerShips) {
    int x, y;
    if (currntPlayerShips < lastPlayerShips) {
        attempt = 0;
        destroying = 0;
        foundDirection = 0;
    }
    lastPlayerShips = currntPlayerShips;
    botShoot(currentMap, height, length, x, y);

    if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
        printAll.printSentence("This cell already hitted");
        return attack(playerTurn, currentMap, height, length, currntPlayerShips);
    }
    if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
        currentMap[x][y].isMiss = 1;
        playerTurn = !playerTurn;
        return std::make_pair(-1, -1);
    }
    if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
        currentMap[x][y].isHit = 1;
        if (!destroying) {
            firstHit = std::make_pair(x, y);
            lastHit = std::make_pair(x, y);
            destroying = 1;
        }
        return std::make_pair(x, y);
    }
}

void BotLvl2::botShoot(std::vector<std::vector<Cell>>& currentMap, int height, int length, int& x, int& y) {
    if (!destroying) {
        x = rand() % height;
        y = rand() % length;
    }
    else {
        findNextTarget(currentMap, x, y, height, length);
    }
}

void BotLvl2::findNextTarget(std::vector<std::vector<Cell>>& currentMap, int& x, int& y, int height, int length) {
    if (attempt >= 4) {
        x = -1;
        y = -1;
        return;
    }

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
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
    else if (!currentMap[newX][newY].isHit && currentMap[newX][newY].isShip) {
        x = newX;
        y = newY;
        lastHit = std::make_pair(x, y);
        foundDirection = 1;
    }
    else {
        directionIndex = (directionIndex + 1) % 4;
        attempt++;
        findNextTarget(currentMap, x, y, height, length);
    }
}

void BotLvl2::reverseDirection() {
    if (directionIndex == 0) directionIndex = 1;
    else if (directionIndex == 1) directionIndex = 0;
    else if (directionIndex == 2) directionIndex = 3;
    else if (directionIndex == 3) directionIndex = 2;
}
