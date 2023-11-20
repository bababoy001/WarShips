#pragma once
#include <vector>
#include "Ship.h"
#include "fuelShip.h"
#include "zalpShip.h"
#include "defoltShip.h"
#include "Cell.h"

class Ships {
public:
    Ships();
    ~Ships();
    void createFleet(std::vector<std::vector<Cell>>& currentMap, int random, int height, int length);
    void checkShipInHit(std::pair<int, int>& pairXY, std::vector<std::vector<Cell>>& currentMap, int height, int length, Ships& currentShips);

    std::vector <Ship*> allShips;
    int countReadyShip;

private:

};
