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
    void cinCoord(int& number, char& letter);
    void printAllMaps(vector<vector<Cell>>& map, vector<vector<Cell>>& enemyMap, int height, int length);
};
