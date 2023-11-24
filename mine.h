#pragma once
#include "Ship.h"
using namespace std;

class mine : public Ship {
public:
    mine(int numDeck);
    void PlaceShip(Ship* ship_temp, vector<vector<Cell>>& currentMap, int height, int length, bool random, bool horizontal) override;
    void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) override;
    void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits);
};