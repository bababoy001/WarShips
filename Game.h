#pragma once
#include <vector>
#include "Cell.h"
#include "Ships.h"
#include "Print.h"
#include "Bot.h"
#include "BotLvl1.h"
#include "BotLvl2.h"
#include "BotLvl3.h"
#include <utility>

using namespace std;

class Game {
public:
    Game();
    ~Game();
    void startGame();

private:
    vector<vector<Cell>> map;
    vector<vector<Cell>> enemyMap;
    Ships myShips;
    Ships enemyShips;
    usualFunc check;
    Print printAll;
    Bot* bot;
    bool gameEnded;
    bool playerTurn;
    int height;
    int length;
    int lvlBot;
    bool random;
    bool zalp = 0;
    int zalpNum = 0;
    vector<vector<Cell>> createMap();
    void enterSettings();
    pair<int, int> attackPlayer(vector<vector<Cell>>& currentMap, int height, int length);
};
