#include "mine.h"
using namespace std;
mine::mine(int numDeck) : Ship(numDeck, "mine") {}

void mine::PlaceShip(Ship* ship_temp, vector<vector<Cell>>& currentMap, int height, int length, bool random, bool horizontal) {
	bool wrongPlace;
	int x;
	int y;
	do {
		wrongPlace = 0;
		if (!random) {
			printAll.printSentence("!(If)!");
			printAll.printSentence("Enter coordinates for place a Mine (number letter): ");
			printAll.cinCoord(x, y);
		}
		else if (random) {
			x = rand() % height;
			y = rand() % length;	
		}

		if (!check.isCellForShip(currentMap, x, y, height, length)) {
			wrongPlace = 1;
		}
		else {
			pair<int, int> pairXY = make_pair(x, y);
			ship_temp->coordinatesShip[pairXY] = *ship_temp;
			ship_temp->coord.coorXY.push_back(pairXY);
		}

		if (wrongPlace) {
			ship_temp->coordinatesShip.clear();
			ship_temp->coord.coorXY.clear();
			printAll.printSentence("Wrong coordinates for place a Mine, try again. ");
		}
	} while (wrongPlace);
	fromVectorToMap(ship_temp, currentMap);
}

void mine::fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) {
	for (int i = 0; i < ship_temp->numDeck; i++) {
		currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'M';
		currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
	}
}

void mine::destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) {
	
}
