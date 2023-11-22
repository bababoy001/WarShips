#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Cell.h"
#include "Coordinates.h"
#include "usualFunc.h"

using namespace std;

class Ship {
public:
    Ship();
    Ship(int numDeck, string name, bool horizontal);
    Ship(int numDeck, bool horizontal);

    virtual void randomPlaceShip(Ship* ship_temp, vector<vector<Cell>>& currentMap, int height, int length);
    virtual void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap);
    virtual void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits);

    int numDeck;
    bool horizontal;
    int countHit;
    string name;
    usualFunc check;
    Coordinates coord;
    map<pair<int, int>, Ship> coordinatesShip;
};
