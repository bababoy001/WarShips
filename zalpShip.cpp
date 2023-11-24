#include "zalpShip.h"
using namespace std;
zalpShip::zalpShip(int numDeck, bool horizontal) : Ship(numDeck, "zalpShip", horizontal) {}
void zalpShip::fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) {
    for (int i = 0; i < ship_temp->numDeck; i++) {
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'C';
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
    }
}

void zalpShip::destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) {
	for (const auto& coord : tempShip->coordinatesShip) {
		int x = coord.first.first;
		int y = coord.first.second;
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (check.isCellInMap(x + dx, y + dy, height, length) && !currentMap[x + dx][y + dy].isHit && !currentMap[x + dx][y + dy].isMiss) {
					currentMap[x + dx][y + dy].isMiss = 1;
				}
			}
		}
	}
	hits.push_back(make_pair(-1, -1));
}