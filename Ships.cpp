#include "Ships.h"
#include <cstdlib>
using namespace std;
Ships::Ships() : countReadyShip(0) {}

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
		if (fuel) {
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
			fuel--;
			allShips.push_back(temp_ship);
		}
		else if (zalp) {
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
			zalp--;
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
}

void Ships::numberOfDecks(int height, int length, bool random) {
	max_length_ship = 4;//4
	max_deck = (height * length * 0.2);
	max_unique = (max_deck * 0.2) / 4;
	if (!random) {
		printAll.numberOfUniqueShips(max_unique, fuel, zalp);
	}
	else if (random) {
		fuel = 1 + rand() % max_unique;
		zalp = max_unique - fuel;
	}
}

void Ships::checkShipInHit(pair<int, int>& pairXY, vector<vector<Cell>>& currentMap, int height, int length, Ships& currentShips) {
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
			for (int i = 0; i < hits.size(); i++) {
				checkShipInHit(hits[i], currentMap, height, length, currentShips);
			}
			currentShips.countReadyShip--;
		}
	}
}