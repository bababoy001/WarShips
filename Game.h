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

class Game {
public:
    Game();
    ~Game();
    void startGame();

private:
    std::vector<std::vector<Cell>> map;
    std::vector<std::vector<Cell>> enemyMap;
    Ships myShips;
    Ships enemyShips;
    usualFunc check;
    bool gameEnded;
    bool playerTurn;
    Print printAll;
    int height;
    int length;
    int lvlBot;
    Bot* bot;

    std::vector<std::vector<Cell>> createMap();
    void enterSettings();
    std::pair<int, int> attackPlayer(std::vector<std::vector<Cell>>& currentMap, int height, int length);
};
