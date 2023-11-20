#include "usualFunc.h"

bool usualFunc::isCellInMap(int x, int y, int height, int length) {
    return (x >= 0) && (y >= 0) && (x < height) && (y < length);
}

bool usualFunc::isCellForShip(std::vector<std::vector<Cell>>& currentMap, int x, int y, int height, int length) {
    if (!isCellInMap(x, y, height, length) || currentMap[x][y].isShip) {
        return false;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (isCellInMap(x + dx, y + dy, height, length) && currentMap[x + dx][y + dy].isShip) {
                return false;
            }
        }
    }
    return true;
}
