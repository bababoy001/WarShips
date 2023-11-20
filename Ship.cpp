#include "Ship.h"
#include <cstdlib>

Ship::Ship() : numDeck(0), horizontal(false), countHit(0) {}

Ship::Ship(int numDeck, std::string name, bool horizontal)
    : numDeck(numDeck), name(name), horizontal(horizontal), countHit(numDeck) {}

Ship::Ship(int numDeck, bool horizontal)
    : numDeck(numDeck), horizontal(horizontal), countHit(numDeck) {}

void Ship::randomPlaceShip(Ship* ship_temp, std::vector<std::vector<Cell>>& currentMap, int height, int length) {
	bool wrongPlace;
	do {
		wrongPlace = 0;
		int x = rand() % height;
		int y = rand() % length;
		for (int i = 0; i < ship_temp->numDeck; i++) {
			if (ship_temp->horizontal) {
				if (!check.isCellForShip(currentMap, x + i, y, height, length)) {
					wrongPlace = 1;
					break;
				}
				else {
					std::pair<int, int> pairXY = std::make_pair(x + i, y);
					ship_temp->coordinatesShip[pairXY] = *ship_temp;
					ship_temp->coord.coorXY.push_back(pairXY);
				}

			}
			else if (!ship_temp->horizontal) {
				if (!check.isCellForShip(currentMap, x, y + i, height, length)) {
					wrongPlace = 1;
					break;
				}
				else {
					std::pair<int, int> pairXY = std::make_pair(x, y + i);
					ship_temp->coordinatesShip[pairXY] = *ship_temp;
					ship_temp->coord.coorXY.push_back(pairXY);
				}
			}
		}
		if (wrongPlace) {
			ship_temp->horizontal = !ship_temp->horizontal;
			ship_temp->coordinatesShip.clear();
			ship_temp->coord.coorXY.clear();
		}
	} while (wrongPlace);
	fromVectorToMap(ship_temp, currentMap);
}

void Ship::fromVectorToMap(Ship* ship_temp, std::vector<std::vector<Cell>>& currentMap) {
	for (int i = 0; i < ship_temp->numDeck; i++) {
		currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'O';
		currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
	}
}

void Ship::destroyShip(std::vector<std::vector<Cell>>& currentMap, Ship* tempShip, int height, int length, std::vector<std::pair<int, int>>& hits) {
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
}
