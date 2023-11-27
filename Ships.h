#pragma once
#include <vector>
#include "Ship.h"
#include "fuelShip.h"
#include "zalpShip.h"
#include "defoltShip.h"
#include "Cell.h"
#include "Print.h"
#include "mine.h"

using namespace std;

class Ships {
public:
    Ships();
    ~Ships();
    void createFleet(vector<vector<Cell>>& currentMap, bool random, int height, int length);
    void checkShipInHit(pair<int, int>& pairXY, vector<vector<Cell>>& currentMap, int height, int length, Ships& currentShips, bool& zalp);
    bool isMine(pair<int, int>& pairXY, vector<vector<Cell>>& map, int height, int length, Ships& enemyShips, bool& zalp, Ships& myShips);
    vector <Ship*> allShips;
    vector <mine> allMines;
    int countReadyShip;
    int countReadyMines;
    vector<pair<int, int>> Allhits;// для всіх влучань (третій бот)
private:
    usualFunc check;
    Print printAll;
    int max_length_ship;
    int max_deck;
    int max_unique;
    int fuelNum;
    int zalpNum;
    int max_mine;
    void numberOfDecks(int height, int length, bool random);
};
