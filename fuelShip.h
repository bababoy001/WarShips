#pragma once
#include "Ship.h"

class fuelShip : public Ship {
public:
    fuelShip(int numDeck, bool horizontal);

    void fromVectorToMap(Ship* ship_temp, std::vector<std::vector<Cell>>& currentMap) override;
    void destroyShip(std::vector<std::vector<Cell>>& currentMap, Ship* tempShip, int height, int length, std::vector<std::pair<int, int>>& hits) override;
};
