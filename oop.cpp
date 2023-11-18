#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


class Cell {
public:
	Cell() {
		isShip = 0;
		isMiss = 0;
		isHit = 0;
		isAlive = 0;
		symbol = ' ';
	}
	bool isShip;
	bool isMiss;
	bool isHit;
	bool isAlive;
	char symbol;
};

class Coordinates {
public:
	Coordinates() {

	}
	vector<pair<int, int>> coorXY;

};

class usualFunc {
public:
	bool isCellInMap(int x, int y, int height, int length) {
		return(x >= 0) && (y >= 0) && (x < height) && (y < length);
	}

	bool isCellForShip(vector<vector<Cell>>& currentMap, int x, int y, int height, int length) {

		if (!isCellInMap(x, y, height, length) || currentMap[x][y].isShip)
		{
			return false;
		}
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (isCellInMap(x + dx, y + dy, height, length) && currentMap[x + dx][y + dy].isShip) {
					return false;
				}
			}
		}
		return true;
	}

	bool areMatricesEqual(const vector<vector<Cell>>& matrix1, const vector<vector<Cell>>& matrix2) {
		if (matrix1.size() != matrix2.size() || matrix1.empty() || matrix1[0].size() != matrix2[0].size()) {
			return false; // Розміри матриць не співпадають
		}

		for (size_t i = 0; i < matrix1.size(); ++i) {
			for (size_t j = 0; j < matrix1[0].size(); ++j) {
				if (matrix1[i][j].isShip != matrix2[i][j].isShip ||
					matrix1[i][j].isMiss != matrix2[i][j].isMiss ||
					matrix1[i][j].isHit != matrix2[i][j].isHit ||
					matrix1[i][j].isAlive != matrix2[i][j].isAlive) {
					return false; // Знайдено різницю в елементах
				}
			}
		}

		return true; // Матриці ідентичні
	}

};

class Ship {
public:
	Ship() : numDeck(0), horizontal(false), countHit(numDeck) {}
	Ship(int numDeck, string name, bool horizontal) {
		this->numDeck = numDeck;
		this->name = name;
		this->horizontal = horizontal;
		this->countHit = numDeck;
	}
	Ship(int numDeck, bool horizontal) {
		this->numDeck = numDeck;
		this->horizontal = horizontal;
		this->countHit = numDeck;
	}
	int numDeck;
	bool horizontal;
	int countHit;
	string name;
	usualFunc check;
	Coordinates coord;
	map<pair<int, int>, Ship> coordinatesShip;

	virtual void randomPlaceShip(Ship* ship_temp, vector<vector<Cell>>& currentMap, int height, int length) {
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
						pair<int, int> pairXY = make_pair(x + i, y);
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
						pair<int, int> pairXY = make_pair(x, y + i);
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
	virtual void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) {
		for (int i = 0; i < ship_temp->numDeck; i++) {
			currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'O';
			currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
		}
	}

	virtual void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) {
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
};

class defoltShip : public Ship {
public:
	defoltShip() : Ship() {}
	defoltShip(int numDeck, bool horizontal) : Ship(numDeck, "defaultShip", horizontal) {}
};

class fuelShip : public Ship {
public:
	fuelShip(int numDeck, bool horizontal) : Ship(numDeck, "fuelShip", horizontal) {}

	void fromVectorToMap(Ship* ship_temp, vector<vector<Cell>>& currentMap) override {
		for (int i = 0; i < ship_temp->numDeck; i++) {
			currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].symbol = 'F';
			currentMap[ship_temp->coord.coorXY[i].first][ship_temp->coord.coorXY[i].second].isShip = 1;
		}
	}

	void destroyShip(vector<vector<Cell>>& currentMap, Ship* tempShip, int height, int length, vector<pair<int, int>>& hits) override {
		for (const auto& coord : tempShip->coordinatesShip) {
			int x = coord.first.first;
			int y = coord.first.second;
			for (int dx = -2; dx <= 2; dx++) {
				for (int dy = -2; dy <= 2; dy++) {
					if (check.isCellInMap(x + dx, y + dy, height, length) && !currentMap[x + dx][y + dy].isHit && !currentMap[x + dx][y + dy].isMiss) {
						currentMap[x + dx][y + dy].isMiss = 1;
						if (currentMap[x + dx][y + dy].isShip) {
							currentMap[x + dx][y + dy].isHit = 1;
							hits.push_back(make_pair(x + dx, y + dy));
						}
					}
				}
			}
		}
	}
};

class zalpShip : public Ship {
public:
	zalpShip(int numDeck, bool horizontal) : Ship(numDeck, "zalpShip", horizontal) {}
};

class Print {
public:

	void lvlChoice(int& lvl) {
		cout << "Enter lvl of bot (1-2): ";
		cin >> lvl;
	}
	void sizeMap(int& height, int& length) {
		cout << "Enter height map: ";
		cin >> height;
		cout << "Enter length map: ";
		cin >> length;
	}
	void printMap(vector<vector<Cell>>& currentMap, int height, int length) {
		cout << "   ";
		for (int j = 0; j < length; j++) {
			char letter = 'a' + j;
			cout << " " << letter;
		}
		cout << endl << "   ";
		for (int j = 0; j <= length * 2; j++) {
			cout << "_";
		}
		cout << endl;


		for (int i = 0; i < height; i++) {
			if (i < 9) {
				cout << i + 1 << " | ";
			}
			else {
				cout << i + 1 << "| ";
			}
			for (int j = 0; j < length; j++) {
				if (currentMap[i][j].isShip) {
					if (currentMap[i][j].isHit) {
						cout << "X ";
						continue;
					}
					cout << currentMap[i][j].symbol << " ";
				}
				else if (currentMap[i][j].isMiss) {
					cout << "* ";
				}
				else {
					cout << "  ";
				}
			}
			cout << "|" << endl;
		}
		cout << "  |";
		for (int j = 0; j <= length * 2; j++) {
			cout << "_";
		}
		cout << "|" << endl;
	}

	void printSentence(string sentence) {
		cout << endl << sentence << endl;
	}

	void cinCoord(int& number, char& letter) {
		cin >> number >> letter;
	}

	void printAllMaps(vector<vector<Cell>>& map, vector<vector<Cell>>& enemyMap, int height, int length) {
		system("cls");
		printSentence("Your Map:");
		printMap(map, height, length);

		printSentence("Enemy's Map:");
		printMap(enemyMap, height, length);
	}

private:

};

class Ships {
public:
	Ships() {
		countReadyShip = 0;
	}
	vector <Ship*> allShips;
	int countReadyShip;

	void createFleet(vector<vector<Cell>>& currentMap, int random, int height, int length) {
		int max_length_ship = 4;// 4
		int max = (height * length * 0.2);
		int max_unique = (max * 0.2) / 4;
		int fuel = max_unique; // зробити функцію запросу для користувача
		int zalp = 0; // зробити функцію запросу для користувача + перевірка

		usualFunc check;
		int temp_size_ship = 1;
		if (random) {
			int currnt = 0;
			while (currnt < max) {
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
						if ((temp_size_ship + currnt) > max) {
							temp_size_ship--;
						}
					} while ((temp_size_ship + currnt) > max);
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
	void checkShipInHit(pair<int, int>& pairXY, vector<vector<Cell>>& currentMap, int height, int length, Ships& currentShips) {
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

private:

};

class Bot {
public:
	virtual pair<int, int> attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips) {
		int x;
		int y;

		botShoot(height, length, x, y);

		if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
			printAll.printSentence("This cell already hitted");
			return attack(playerTurn, currentMap, height, length, currntPlayerShips);
		}
		if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
			currentMap[x][y].isMiss = 1;
			playerTurn = !playerTurn;
			return make_pair(-1, -1);
		}
		if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
			currentMap[x][y].isHit = 1;
			return make_pair(x, y);
		}
	}

	virtual void botShoot(int height, int length, int& x, int& y) {
		x = rand() % height;
		y = rand() % length;
	}

private:
	usualFunc check;
	Print printAll;
	bool destroying;
};

class BotLvl1 : public Bot {
public:

	BotLvl1() {}



private:
	usualFunc check;
	Print printAll;
};

class BotLvl2 : public Bot {
public:
	BotLvl2() : firstHit(-1, -1), lastHit(-1, -1), destroying(false), directionIndex(0), foundDirection(false), attempt(0), lastPlayerShips(0){}

	pair<int, int> attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips) override {
		int x, y;
		if (currntPlayerShips < lastPlayerShips) {
			destroying = 0;
		}
		lastPlayerShips = currntPlayerShips;
		botShoot(currentMap, height, length, x, y);

		if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
			printAll.printSentence("This cell already hitted");
			return attack(playerTurn, currentMap, height, length, currntPlayerShips);
		}
		if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
			currentMap[x][y].isMiss = 1;
			playerTurn = !playerTurn;
			return make_pair(-1, -1);
		}
		if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
			currentMap[x][y].isHit = 1;
			if (!destroying) {
				firstHit = make_pair(x, y);
				lastHit = make_pair(x, y);
				destroying = 1;
			}
			return make_pair(x, y);
		}
	}

private:
	pair<int, int> firstHit;
	pair<int, int> lastHit;
	bool destroying;
	int directionIndex;
	bool foundDirection;
	int attempt;
	int lastPlayerShips;
	usualFunc check;
	Print printAll;

	void botShoot(vector<vector<Cell>>& currentMap, int height, int length, int& x, int& y) {
		if (!destroying) {
			x = rand() % height;
			y = rand() % length;
		}
		else {
			findNextTarget(currentMap, x, y, height, length);
		}
	}

	void findNextTarget(vector<vector<Cell>>& currentMap, int& x, int& y, int height, int length) {
		if (attempt >= 4) {
			x = -1;
			y = -1;
			return;
		}

		vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
		int dx = directions[directionIndex].first;
		int dy = directions[directionIndex].second;
		int newX = lastHit.first + dx;
		int newY = lastHit.second + dy;

		if (!check.isCellInMap(newX, newY, height, length)) {
			if (foundDirection) {
				lastHit = firstHit;
				reverseDirection();
			}
			else {
				directionIndex = (directionIndex + 1) % 4;
				attempt++;
			}
			
			return findNextTarget(currentMap, x, y, height, length);
		}

		if (check.isCellInMap(newX, newY, height, length) && !currentMap[newX][newY].isHit && !currentMap[newX][newY].isMiss && !currentMap[newX][newY].isShip) {
			if (foundDirection) {
				x = newX;
				y = newY;
				lastHit = firstHit;
				reverseDirection();
			}
			else {
				directionIndex = (directionIndex + 1) % 4;
				attempt++;
				x = newX;
				y = newY;
				return;
			}
		}
		else if (!currentMap[newX][newY].isHit && currentMap[newX][newY].isShip) {
			x = newX;
			y = newY;
			lastHit = make_pair(x, y);
			foundDirection = 1;
		}
		else {
			directionIndex = (directionIndex + 1) % 4;
			attempt++;
			findNextTarget(currentMap, x, y, height, length);
		}
	}

	void reverseDirection() {
		if (directionIndex == 0) directionIndex = 1;
		else if (directionIndex == 1) directionIndex = 0;
		else if (directionIndex == 2) directionIndex = 3;
		else if (directionIndex == 3) directionIndex = 2;
	}

	
};

class BotLvl3 : public Bot {
public:
	BotLvl3() {}


};

class Game {
public:
	Game() : height(10), length(10), lvlBot(0), gameEnded(false), playerTurn(true) {}

	vector<vector<Cell>> createMap() {
		return vector<vector<Cell>>(height, vector<Cell>(length));
	}

	void enterSettings() {
		printAll.sizeMap(height, length);
		printAll.lvlChoice(lvlBot);
		switch (lvlBot) {
		case 1:
			bot = new BotLvl1();
			break;
		case 2:
			bot = new BotLvl2();
			break;
		case 3:
			bot = new BotLvl3();
			break;
		default:
			printAll.printSentence("Invalid level. Setting to level 1");
			bot = new BotLvl1();
			break;
		}
	}


	void startGame() {
		enterSettings();
		map = createMap();
		enemyMap = createMap();
		myShips.createFleet(map, 1, height, length);
		enemyShips.createFleet(enemyMap, 1, height, length);
		pair<int, int> pairForMiss = make_pair(-1, -1);
		while (!gameEnded) {

			if (playerTurn) {
				printAll.printAllMaps(map, enemyMap, height, length);
				pair<int, int> pairXY = attackPlayer(enemyMap, height, length);
				if (pairXY != pairForMiss) {
					myShips.checkShipInHit(pairXY, enemyMap, height, length, enemyShips);
				}
			}
			else {
				pair<int, int> pairXY = bot->attack(playerTurn, map, height, length, myShips.countReadyShip);
				if (pairXY != pairForMiss) {
					enemyShips.checkShipInHit(pairXY, map, height, length, myShips);
				}
			}

			if (enemyShips.countReadyShip == 0) {
				printAll.printAllMaps(map, enemyMap, height, length);
				printAll.printSentence("Congratulations! You've destroyed all enemy ships. You win!");
				gameEnded = true;
			}

			if (myShips.countReadyShip == 0) {
				printAll.printAllMaps(map, enemyMap, height, length);
				printAll.printSentence("Game over! All your ships have been destroyed. You lose.");
				gameEnded = true;
			}
		}
	}

private:
	vector<vector<Cell>> map;
	vector<vector<Cell>> enemyMap;
	Ships myShips;
	Ships enemyShips;
	usualFunc check;
	bool gameEnded;
	bool playerTurn;
	Print printAll;
	int height;
	int length;
	int lvlBot;
	Bot* bot;

	virtual pair<int, int> attackPlayer(vector<vector<Cell>>& currentMap, int height, int length) {
		int x;
		int y;

		printAll.printSentence("Enter coordinates (number letter): ");
		char letter;
		int number;
		printAll.cinCoord(number, letter);

		x = number - 1;
		y = letter - 'a';

		if (!check.isCellInMap(x, y, height, length)) {
			printAll.printSentence("Wrong coordinates");
			return attackPlayer(currentMap, height, length);
		}
		if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
			printAll.printSentence("This cell already hitted");
			return attackPlayer(currentMap, height, length);
		}
		if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
			currentMap[x][y].isMiss = 1;
			playerTurn = !playerTurn;
			return make_pair(-1, -1);
		}
		if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
			currentMap[x][y].isHit = 1;
			return make_pair(x, y);
		}
	}
};

int main()
{
	srand(time(NULL));
	Game game;

	game.startGame();

	return 0;
}