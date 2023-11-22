#pragma once
#include <vector>
#include "Cell.h"
using namespace std;
class usualFunc {
public:
    bool isCellInMap(int x, int y, int height, int length);
    bool isCellForShip(vector<vector<Cell>>& currentMap, int x, int y, int height, int length);
};
