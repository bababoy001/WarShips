#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"

class Print {
public:
    void lvlChoice(int& lvl);
    void sizeMap(int& height, int& length);
    void printMap(std::vector<std::vector<Cell>>& currentMap, int height, int length);
    void printSentence(std::string sentence);
    void cinCoord(int& number, char& letter);
    void printAllMaps(std::vector<std::vector<Cell>>& map, std::vector<std::vector<Cell>>& enemyMap, int height, int length);
};
