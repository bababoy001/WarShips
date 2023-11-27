#pragma once
#include <vector>
#include <utility>
#include "Cell.h"
#include "Print.h"
#include "usualFunc.h"
#include <cstdlib>
using namespace std;

class Bot {
public:
    virtual pair<int, int> attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips, vector<pair<int, int>>& mines);
    virtual void botShoot(int height, int length, int& x, int& y);

protected:
    usualFunc check;
    Print printAll;
    bool destroying;
};
