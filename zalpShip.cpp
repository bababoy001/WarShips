#include "zalpShip.h"
using namespace std;
zalpShip::zalpShip(int numDeck, bool horizontal) : Ship(numDeck, "zalpShip", horizontal) {}
void zalpShip::fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) {
    for (int i = 0; i < ship_temp->numDeck; i++) {
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'Z';
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
    }
}