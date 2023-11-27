#pragma once
#include <vector>
#include <utility>
#include "Cell.h"
#include "usualFunc.h"
#include "Print.h"
using namespace std;

class mine {
public:
public:
    mine();
    void PlaceMine(mine* mine_temp, vector<vector<Cell>>& currentMap, int height, int length, bool random);
    pair<int, int> coordinatesMine;
    usualFunc check;
    Print printAll;
};