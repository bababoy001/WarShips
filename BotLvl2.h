#pragma once
#include "Bot.h"
#include <utility>
#include <vector>
#include "Cell.h"
using namespace std;
class BotLvl2 : public Bot {
public:
    BotLvl2();

    pair<int, int> attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips, int currntPlayerMines) override;

private:
    pair<int, int> firstHit;
    pair<int, int> lastHit;
    bool destroying;
    int directionIndex;
    bool foundDirection;
    int attempt;
    int lastPlayerShips;
    int lastPlayerMines;
    void botShoot(vector<vector<Cell>>& currentMap, int height, int length, int& x, int& y);
    void findNextTarget(vector<vector<Cell>>& currentMap, int& x, int& y, int height, int length);
    void reverseDirection();
};
