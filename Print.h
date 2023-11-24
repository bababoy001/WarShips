#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"

using namespace std;

class Print {
public:
    void lvlChoice(int& lvl);
    void sizeMap(int& height, int& length);
    void printMap(vector<vector<Cell>>& currentMap, int height, int length);
    void printSentence(string sentence);
    void cinCoord(int& x, int& y);
    void printAllMaps(vector<vector<Cell>>& map, vector<vector<Cell>>& enemyMap, int height, int length);
    void numberOfUniqueShips(int max_unique, int& fuel, int& zalp);
    void isShipHorizonal(bool& horizontal);
    void createShip(int& temp_size_ship, bool& horizontal, int currnt, int max_deck, int max_length_ship);
    void placeShip(bool& random);
};
