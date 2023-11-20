#pragma once
#include "Bot.h"
#include <utility>
#include <vector>
#include "Cell.h"

class BotLvl2 : public Bot {
public:
    BotLvl2();

    std::pair<int, int> attack(bool& playerTurn, std::vector<std::vector<Cell>>& currentMap, int height, int length, int currntPlayerShips) override;

private:
    std::pair<int, int> firstHit;
    std::pair<int, int> lastHit;
    bool destroying;
    int directionIndex;
    bool foundDirection;
    int attempt;
    int lastPlayerShips;

    void botShoot(std::vector<std::vector<Cell>>& currentMap, int height, int length, int& x, int& y);
    void findNextTarget(std::vector<std::vector<Cell>>& currentMap, int& x, int& y, int height, int length);
    void reverseDirection();
};
