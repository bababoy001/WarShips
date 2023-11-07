#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#define height 10
#define length 10
#define countShip 10

using namespace std;



class Cell{
public:
	Cell() {
		isShip = 0;
		isMiss = 0;
		isHit = 0;
		isAlive = 0;
	}
	bool isShip;
	bool isMiss;
	bool isHit;
	bool isAlive;
};


class Ship {
public:
	Ship(int numDeck, int typeShip, string nameCategoryShip, bool horizontal) {
		this->numDeck = numDeck;
		this->typeShip = typeShip;
		this->nameCategoryShip = nameCategoryShip;
		this->horizontal = horizontal;
	}

	int numDeck;
	int typeShip;
	bool horizontal;
	string nameCategoryShip;
	vector<int> coorX;
	vector<int> coorY;
};



class Ships {
public:
	Ships() {
		
	}
	vector <Ship> allShips;
	int countReadyShip = 0;
	

	void makeShip(Ship* ship_temp, Cell(*map)[length], bool random) {
		if (random) {
			randomPlaceShip(ship_temp, map);
		}
		if (!random) {
			//PlaceShip(*ship_temp);
		}

	}

	bool isCellForShip(Cell(*map)[length], int x, int y) {

		if (!isCellInMap(x, y) || map[x][y].isShip)
		{
			return false;
		}
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (isCellInMap(x + dx, y + dy) && map[x + dx][y + dy].isShip) {
					return false;
				}
			}
		}
		return true;
	}

	void randomPlaceShip(Ship *ship_temp, Cell(*map)[length]) {
		bool wrongPlace;
		do {
			wrongPlace = 0;
			int x = rand() % height;
			int y = rand() % length;
			for (int i = 0; i < ship_temp->numDeck; i++) {
				if (ship_temp->horizontal) {
					if (!isCellForShip(map, x + i, y)) {
						wrongPlace = 1;
						break;
					}
					else {
						ship_temp->coorX.push_back(x + i);
						ship_temp->coorY.push_back(y);
					}

				}
				else if (!ship_temp->horizontal) {
					if (!isCellForShip(map, x, y + i)) {
						wrongPlace = 1;
						break;
					}
					else {
						ship_temp->coorX.push_back(x);
						ship_temp->coorY.push_back(y + i);
					}
				}
			}
			if (wrongPlace) {
				ship_temp->horizontal = !ship_temp->horizontal;
				ship_temp->coorX.clear();
				ship_temp->coorY.clear();
			}
		} while (wrongPlace);

		allShips.push_back(*ship_temp);
		fromVectorToMap(ship_temp, map);
		countReadyShip++;

	}

	bool isCellInMap(int x, int y) {
		return(x >= 0) && (y >= 0) && (x < height) && (y < length);
	}

	void createFleet(Cell(*map)[length]) {
		// Создание 1 четырехпалубного корабля
		Ship fourDecker(4, 1, "четырехпалубный", rand() % 2);
		makeShip(&fourDecker, map, true);

		// Создание 2 трехпалубных кораблей
		for (int i = 0; i < 2; ++i) {
			Ship threeDecker(3, 1, "трехпалубный", rand() % 2);
			makeShip(&threeDecker, map, true);
		}

		// Создание 3 двупалубных кораблей
		for (int i = 0; i < 3; ++i) {
			Ship twoDecker(2, 1, "двупалубный", rand() % 2);
			makeShip(&twoDecker, map, true);
		}

		// Создание 4 однопалубных кораблей
		for (int i = 0; i < 4; ++i) {
			Ship oneDecker(1, 1, "однопалубный", rand() % 2);
			makeShip(&oneDecker, map, true);
		}
	}
private:
	void fromVectorToMap(Ship* ship_temp, Cell(*map)[length]) {
		for (int i = 0; i < ship_temp->numDeck; i++) {
			map[ship_temp->coorX[i]][ship_temp->coorY[i]].isShip = 1;
		}
	}
};


void printMap(Cell(*map)[length]) {
	cout << "   ";
	for (int j = 1; j <= length; j++) {
		cout << " " << j;
	}

	cout << endl << "   _____________________" << endl;
	cout << "  |                     |" << endl;

	for (int i = 0; i < height; i++) {
		char letter = 'a' + i;

		cout << letter << " | ";

		for (int j = 0; j < length; j++) {
			if (map[i][j].isShip) {
				cout << "O ";
			}
			else if (map[i][j].isHit) {
				cout << "X ";
			}
			else if (map[i][j].isMiss) {
				cout << "` ";
			}
			else {
				cout << "  ";
			}
		}

		cout << "|" << endl;
	}
	cout << "  |_____________________|";
}

void playerAttack(Cell(*enemyMap)[length]) {
	cout << "Enter coordinates to attack (e.g., a1): ";
	char letter;
	int number;
	cin >> letter >> number;

	int x = letter - 'a';
	int y = number - 1;

	if (enemyMap[x][y].isMiss || enemyMap[x][y].isHit) {
		cout << "You've already attacked this cell. Try again." << endl;
		playerAttack(enemyMap);
	}
	else {
		if (enemyMap[x][y].isShip) {
			cout << "Hit!" << endl;
			enemyMap[x][y].isHit = true;
		}
		else {
			cout << "Miss!" << endl;
			enemyMap[x][y].isMiss = true;
		}
	}
}


int main()
{
	srand(time(NULL));
	Cell map[height][length]; //двовимірний масив для прязки координат союзних кораблів на мапі
	Cell enemyMap[height][length]; //двовимірний масив для прязки координат ворожих кораблів на мапі
	Ships myShips;
	Ships enemyShips;
	myShips.createFleet(map);
	enemyShips.createFleet(enemyMap);
	
	
	return 0;

}
