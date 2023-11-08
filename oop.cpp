	#include <iostream>
	#include <ctime>
	#include <windows.h>
	#include <conio.h>
	#include <string>
	#include <vector>
	#include <map>

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
		Ship() : numDeck(0), typeShip(0), horizontal(false) {}
		Ship(int numDeck, int typeShip, string nameCategoryShip, bool horizontal) {
			this->numDeck = numDeck;
			this->typeShip = typeShip;
			this->nameCategoryShip = nameCategoryShip;
			this->horizontal = horizontal; 
			this->countHit = numDeck;
		}

		int numDeck;
		int typeShip;
		bool horizontal;
		int countHit;
		string nameCategoryShip;
		map<pair<int, int>, Ship> coordinates;
		vector<int> coorX;
		vector<int> coorY;
	};



	class Ships {
	public:
		Ships() {
			countReadyShip = 0;
		}
		vector <Ship> allShips;
		int countReadyShip;

		void createFleet(Cell(*map)[length]) {
			Ship fourDecker(4, 1, "4", rand() % 2);
			makeShip(&fourDecker, map, true);

			for (int i = 0; i < 2; ++i) {
				Ship threeDecker(3, 1, "3", rand() % 2);
				makeShip(&threeDecker, map, true);
			}

			for (int i = 0; i < 3; ++i) {
				Ship twoDecker(2, 1, "2", rand() % 2);
				makeShip(&twoDecker, map, true);
			}

			for (int i = 0; i < 4; ++i) {
				Ship oneDecker(1, 1, "1", rand() % 2);
				makeShip(&oneDecker, map, true);
			}
		}
	private:
		void fromVectorToMap(Ship* ship_temp, Cell(*map)[length]) {
			for (int i = 0; i < ship_temp->numDeck; i++) {
				map[ship_temp->coorX[i]][ship_temp->coorY[i]].isShip = 1;
				pair<int, int> pairXY = make_pair(ship_temp->coorX[i], ship_temp->coorY[i]);
				allShips.at(countReadyShip).coordinates[pairXY] = *ship_temp;
			}
		}
		void makeShip(Ship* ship_temp, Cell(*map)[length], bool random) {
			if (random) {
				randomPlaceShip(ship_temp, map);
			}
			if (!random) {
				//PlaceShip(*ship_temp);
			}

		}
		bool isCellInMap(int x, int y) {
			return(x >= 0) && (y >= 0) && (x < height) && (y < length);
		}
		void randomPlaceShip(Ship* ship_temp, Cell(*map)[length]) {
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
	};

	class Game {
	public:
		Game(){
			myShips.createFleet(map);
			enemyShips.createFleet(enemyMap);
			gameEnded = 0;
			playerTurn = 1;
		}
		Cell map[height][length];
		Cell enemyMap[height][length];
		Ships myShips;
		Ships enemyShips;
		bool gameEnded;
		bool playerTurn;
		void startGame(){
			while (!gameEnded) {

				if (playerTurn) {
					system("cls");
					cout << "Your Map:" << endl;
					printMap(map);

					cout << endl << "Enemy's Map:" << endl;

					printMap(enemyMap);
					attack(enemyMap);
				}
				else {
					attack(map);
				}

				if (enemyShips.countReadyShip == 0) {
					cout << "Congratulations! You've destroyed all enemy ships. You win!" << endl;
					gameEnded = 1;
				}


				if (myShips.countReadyShip == 0) {
					cout << "Game over! All your ships have been destroyed. You lose." << endl;
					gameEnded = 1;
				}
			}
		}
	private:
		void attack(Cell(*currentMap)[length]) {
			int x;
			int y;

			if (playerTurn) {
				cout << endl << "Enter coordinates: " << endl;
				char letter;
				int number;
				cin >> letter >> number;

				x = letter - 'a';
				y = number - 1;

				if (!isCellInMap(x, y)) {
					cout << endl << "Wrong coordinates" << endl;
					attack(currentMap);
				}
			}
			else if (!playerTurn) {
				x = rand() % height;
				y = rand() % length;
			
			}
			if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
				cout << endl << "This cell already hitted" << endl;
				attack(currentMap);
			}
			if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
				currentMap[x][y].isMiss = 1;
				playerTurn = !playerTurn;
			}
			if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
				currentMap[x][y].isHit = 1;
				isShipDestroyed(x, y, currentMap);
			}

		}

		void isShipDestroyed(int x, int y, Cell(*currentMap)[length]) {
			pair<int, int> pairXY = make_pair(x, y);
			Ship* tempShip = nullptr;

			vector<Ship>& ships = (currentMap == map) ? myShips.allShips : enemyShips.allShips;

			for (Ship& ship : ships) {
				auto it = ship.coordinates.find(pairXY);
				if (it != ship.coordinates.end()) {
					tempShip = &ship;
					break;
				}
			}

			if (tempShip) {
				tempShip->countHit -= 1;

				if (tempShip->countHit == 0) {
					destroyShip(currentMap, tempShip);

					if (currentMap == map) {
						myShips.countReadyShip--;
					}
					else {
						enemyShips.countReadyShip--;
					}
				}
			}
		}

		void destroyShip(Cell(*currentMap)[length], Ship* tempShip) {
			int x;
			int y;
			for (int i = 0; i < tempShip->numDeck; i++) {
				x = tempShip->coorX[i];
				y = tempShip->coorY[i];
				for (int dx = -1; dx <= 1; dx++) {
					for (int dy = -1; dy <= 1; dy++) {
						if (isCellInMap(x + dx, y + dy) && !currentMap[x + dx][y + dy].isHit && !currentMap[x + dx][y + dy].isMiss) {
							currentMap[x + dx][y + dy].isMiss = 1;
						}
					}
				}
			}
		}



		bool isCellInMap(int x, int y) {
			return(x >= 0) && (y >= 0) && (x < height) && (y < length);
		}

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
						if (map[i][j].isHit) {
							cout << "X ";
							continue;
						}
						cout << "O ";
					}
					else if (map[i][j].isMiss) {
						cout << "* ";
					}
					else {
						cout << "  ";
					}
				}

				cout << "|" << endl;
			}
			cout << "  |_____________________|";
		}
	};

	int main()
	{
		srand(time(NULL));
		Game game;
		game.startGame();
	
	
		return 0;

	}