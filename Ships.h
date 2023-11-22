#pragma once
#include <vector>
#include "Ship.h"
#include "fuelShip.h"
#include "zalpShip.h"
#include "defoltShip.h"
#include "Cell.h"
#include "Print.h"

using namespace std;

class Ships {
public:
    Ships();
    ~Ships();
    void createFleet(vector<vector<Cell>>& currentMap, bool random, int height, int length);
    void checkShipInHit(pair<int, int>& pairXY, vector<vector<Cell>>& currentMap, int height, int length, Ships& currentShips);

    vector <Ship*> allShips;
    int countReadyShip;

private:
    usualFunc check;
    Print printAll;
    int max_length_ship;
    int max_deck;
    int max_unique;
    int fuel;
    int zalp;
    void numberOfDecks(int height, int length, bool random);
};
