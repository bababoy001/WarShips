#pragma once
#include "Bot.h"
using namespace std;
class BotLvl3 : public Bot {
public:
    BotLvl3();
    pair<int, int> attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips, vector<pair<int, int>>& mines, pair<int, int >& pairHitedBoards) override;

private:
    pair<int, int> firstHit;
    pair<int, int> lastHit;
    bool destroying;
    int directionIndex;
    bool foundDirection;
    int attempt;
    int lastPlayerShips;
    void botShoot(vector<vector<Cell>>& currentMap, int height, int length, int& x, int& y);
    void findNextTarget(vector<vector<Cell>>& currentMap, int& x, int& y, int height, int length);
    void reverseDirection();
};