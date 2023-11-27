#include "fuelShip.h"
using namespace std;
fuelShip::fuelShip(int numDeck, bool horizontal) : Ship(numDeck, "fuelShip", horizontal) {}

void fuelShip::fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) {
    for (int i = 0; i < ship_temp->numDeck; i++) {
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'F';
        currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
    }
}

void fuelShip::destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) {
	for (const auto& coord : tempShip->coordinatesShip) {
		int x = coord.first.first;
		int y = coord.first.second;
		for (int dx = -2; dx <= 2; dx++) {
			for (int dy = -2; dy <= 2; dy++) {
				if (check.isCellInMap(x + dx, y + dy, height, length) && !currentMap[x + dx][y + dy].isHit && !currentMap[x + dx][y + dy].isMiss) {
					currentMap[x + dx][y + dy].isMiss = 1;
					if (currentMap[x + dx][y + dy].isShip) {// || currentMap[x + dx][y + dy].isMine
						currentMap[x + dx][y + dy].isHit = 1;
						hits.push_back(make_pair(x + dx, y + dy));
					}
					else if (currentMap[x + dx][y + dy].isMine) {
						currentMap[x + dx][y + dy].isMine = 1;
						currentMap[x + dx][y + dy].isHit = 1;
					}
				}
			}
		}
	}
}
