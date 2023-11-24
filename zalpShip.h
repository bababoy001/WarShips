#pragma once
#include "Ship.h"
using namespace std;
class zalpShip : public Ship {
public:
    zalpShip(int numDeck, bool horizontal);
    void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap);
    void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) override;
};
