#pragma once
#include <vector>
#include "Cell.h"

class usualFunc {
public:
    bool isCellInMap(int x, int y, int height, int length);
    bool isCellForShip(std::vector<std::vector<Cell>>& currentMap, int x, int y, int height, int length);
};
