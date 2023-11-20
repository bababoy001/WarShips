#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Cell.h"
#include "Coordinates.h"
#include "usualFunc.h"

class Ship {
public:
    Ship();
    Ship(int numDeck, std::string name, bool horizontal);
    Ship(int numDeck, bool horizontal);

    virtual void randomPlaceShip(Ship* ship_temp, std::vector<std::vector<Cell>>& currentMap, int height, int length);
    virtual void fromVectorToMap(Ship* ship_temp, std::vector<std::vector<Cell>>& currentMap);
    virtual void destroyShip(std::vector<std::vector<Cell>>& currentMap, Ship* tempShip, int height, int length, std::vector<std::pair<int, int>>& hits);

    int numDeck;
    bool horizontal;
    int countHit;
    std::string name;
    usualFunc check;
    Coordinates coord;
    std::map<std::pair<int, int>, Ship> coordinatesShip;
};
