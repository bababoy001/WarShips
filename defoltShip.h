#pragma once
#include "Ship.h"
using namespace std;

class defoltShip : public Ship {
public:
    defoltShip();
    defoltShip(int numDeck, bool horizontal);
};
