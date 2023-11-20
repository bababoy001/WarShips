#pragma once
#include <vector>
#include <utility>
#include "Cell.h"
#include "Print.h"
#include "usualFunc.h"
#include <cstdlib>

class Bot {
public:
    virtual std::pair<int, int> attack(bool& playerTurn, std::vector<std::vector<Cell>>& currentMap, int height, int length, int currntPlayerShips);
    virtual void botShoot(int height, int length, int& x, int& y);

protected:
    usualFunc check;
    Print printAll;
    bool destroying;
};
