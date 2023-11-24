#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Cell.h"
#include "Coordinates.h"
#include "usualFunc.h"
#include "Print.h"

using namespace std;

class Ship {
public:
    Ship();
    Ship(int numDeck, string name, bool horizontal);
    Ship(int numDeck, bool horizontal);
    Ship(int numDeck, string name);

    virtual void PlaceShip(Ship* ship_temp, vector<vector<Cell>>& currentMap, int height, int length, bool random, bool horizontal);
    virtual void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap);
    virtual void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits);
    void randomPlace(int& x, int& y, int height, int length);
    void place(int& x, int& y, int height, int length, bool horizontal);
    int numDeck;
    bool horizontal;
    int countHit;
    string name;
    Coordinates coord;
    map<pair<int, int>, Ship> coordinatesShip;
    usualFunc check;
    Print printAll;
};
