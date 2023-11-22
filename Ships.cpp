#include "Ships.h"
#include <cstdlib>
using namespace std;
Ships::Ships() : countReadyShip(0) {}

Ships::~Ships() {
    for (auto ship : allShips) {
        delete ship;
    }
}

void Ships::createFleet(vector<vector<Cell>>& currentMap, int random, int height, int length) {
	int max_length_ship = 4;// 4
	int max_deck = (height * length * 0.2);
	int max_unique = (max_deck * 0.2) / 4;
	int fuel = max_unique; // зробити функцію запросу для користувача
	int zalp = 0; // зробити функцію запросу для користувача + перевірка

	usualFunc check;
	int temp_size_ship = 1;
	if (random) {
		int currnt = 0;
		while (currnt < max_deck) {
			if (fuel) {
				/*temp_ship = fuelShip(4, rand() % 2);*/
				Ship* temp_ship = new fuelShip(4, rand() % 2);
				temp_ship->randomPlaceShip(temp_ship, currentMap, height, length);
				currnt += 4;
				fuel--;
				allShips.push_back(temp_ship);
				countReadyShip++;
			}
			else if (zalp) {
				/*temp_ship = zalpShip(4, rand() % 2);*/
				Ship* temp_ship = new zalpShip(4, rand() % 2);
				temp_ship->randomPlaceShip(temp_ship, currentMap, height, length);
				currnt += 4;
				zalp--;
				allShips.push_back(temp_ship);
				countReadyShip++;
			}
			else {
				temp_size_ship = 1 + rand() % max_length_ship;
				do {
					if ((temp_size_ship + currnt) > max_deck) {
						temp_size_ship--;
					}
				} while ((temp_size_ship + currnt) > max_deck);
				Ship* temp_ship = new defoltShip(temp_size_ship, rand() % 2);
				temp_ship->randomPlaceShip(temp_ship, currentMap, height, length);
				currnt += temp_size_ship;
				allShips.push_back(temp_ship);
				countReadyShip++;
			}
		}
	}
	if (!random) {
		//PlaceShip(*ship_temp);
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
