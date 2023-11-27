#pragma once
using namespace std;
class Cell {
public:
    Cell();

    bool isShip;
    bool isMiss;
    bool isHit;
    bool isAlive;
    bool isMine;
    bool isHitFromMine;
    char symbol;
};
