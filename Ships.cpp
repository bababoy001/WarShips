#include "Ships.h"
#include <cstdlib>
using namespace std;
Ships::Ships() : countReadyShip(0), countReadyMines(0) {}

Ships::~Ships() {
    for (auto ship : allShips) {
        delete ship;
    }
}

void Ships::createFleet(vector<vector<Cell>>& currentMap, bool random, int height, int length) {
	numberOfDecks(height, length, random);
	int temp_size_ship = 1;
	bool horizontal = 0;
	int currnt = 0;
	while (currnt < max_deck) {
		if (fuelNum) {
			if (random) {
				horizontal = rand() % 2;
			}
			else {
				printAll.printMap(currentMap, height, length);
				printAll.isShipHorizonal(horizontal);
			}
			Ship* temp_ship = new fuelShip(4, horizontal);
			temp_ship->PlaceShip(temp_ship, currentMap, height, length, random, horizontal);
			currnt += 4;
			fuelNum--;
			allShips.push_back(temp_ship);
		}
		else if (zalpNum) {
			if (random) {
				horizontal = rand() % 2;
			}
			else{
				printAll.printMap(currentMap, height, length);
				printAll.isShipHorizonal(horizontal);
			}
			Ship* temp_ship = new zalpShip(4, horizontal);
			temp_ship->PlaceShip(temp_ship, currentMap, height, length, random, horizontal);
			currnt += 4;
			zalpNum--;
			allShips.push_back(temp_ship);
		}
		else {
			if (random) {
				temp_size_ship = 1 + rand() % max_length_ship;
				do {
					if ((temp_size_ship + currnt) > max_deck) {
						temp_size_ship--;
					}
				} while ((temp_size_ship + currnt) > max_deck);
				horizontal = rand() % 2;
			}
			else if (!random) {
				printAll.printMap(currentMap, height, length);
				printAll.createShip(temp_size_ship, horizontal, currnt, max_deck, max_length_ship);
			}
			Ship* temp_ship = new defoltShip(temp_size_ship, horizontal);
			temp_ship->PlaceShip(temp_ship, currentMap, height, length, random, horizontal);
			allShips.push_back(temp_ship);
			currnt += temp_size_ship;
		}
		countReadyShip++;
		system("cls");
	}
	currnt = 0;
	while (currnt < max_mine) {
		printAll.printMap(currentMap, height, length);
		Ship* temp_ship = new mine(1);
		temp_ship->PlaceShip(temp_ship, currentMap, height, length, random, horizontal);
		currnt += 1;
		allMines.push_back(temp_ship);
		countReadyMines++;
		system("cls");
	}
}

void Ships::numberOfDecks(int height, int length, bool random) {
	max_mine = (height * length * 0.02);
	max_length_ship = 4;//4
	max_deck = (height * length * 0.2);
	max_unique = (max_deck * 0.2) / 4;
	if (!random) {
		printAll.numberOfUniqueShips(max_unique, fuelNum, zalpNum);
	}
	else if (random) {
		fuelNum = 1 + rand() % max_unique;
		zalpNum = max_unique - fuelNum;
	}
}

void Ships::checkShipInHit(pair<int, int>& pairXY, vector<vector<Cell>>& currentMap, int height, int length, Ships& currentShips, bool& zalp) {
	Ship* tempShip = nullptr;
	vector<Ship*> ships = currentShips.allShips;

	for (Ship* ship : ships) {
		auto it = ship->coordinatesShip.find(pairXY);
		if (it != ship->coordinatesShip.end()) {
			tempShip = ship;
			break;
		}
	}
	if (tempShip) {
		tempShip->countHit -= 1;
		if (tempShip->countHit == 0) {
			vector<pair<int, int>> hits;
			tempShip->destroyShip(currentMap, tempShip, height, length, hits);
			if (hits.size() == 1 && hits[0] == make_pair(-1, -1)) {
				zalp = 1;
			}
			else {
				for (int i = 0; i < hits.size(); i++) {
					checkShipInHit(hits[i], currentMap, height, length, currentShips, zalp);
				}
			}

			currentShips.countReadyShip--;
		}
	}
}

bool Ships::isMine(pair<int, int>& pairXY, vector<vector<Cell>>& map, int height, int length, Ships& enemyShips, bool& zalp, Ships& myShips) {
	Ship* tempMine = nullptr;
	vector<Ship*> mines = enemyShips.allMines;

	for (Ship* mine : mines) {
		auto it = mine->coordinatesShip.find(pairXY);
		if (it != mine->coordinatesShip.end()) {
			tempMine = mine;
			break;
		}
	}
	if (tempMine) {
		tempMine->countHit -= 1;
		int x = pairXY.first;
		int y = pairXY.second;
		if (!map[x][y].isHit && !map[x][y].isMiss && !map[x][y].isShip) {
			map[x][y].isMiss = 1;
		}
		if (map[x][y].isShip && !map[x][y].isHit) {
			map[x][y].isHit = 1;
			enemyShips.checkShipInHit(pairXY, map, height, length, myShips, zalp);
		}
		enemyShips.countReadyMines--;
		return true;
	}
	return false;
}