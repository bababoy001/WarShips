#pragma once
#include "Ship.h"
using namespace std;

class fuelShip : public Ship {
public:
    fuelShip(int numDeck, bool horizontal);

    void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) override;
    void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) override;
};
