#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#define height 10
#define length 10
using namespace std;



class Cell{
public:
	Cell() {
		isShip = 0;
		isShoot = 0;
		isHit = 0;
		isAlive = 0;
	}
	bool isShip;
	bool isShoot;
	bool isHit;
	bool isAlive;
};


class Ships {
public:
	Ships(int numDeck, int typeShip, string nameCategoryShip, bool horizontal) {
		this->numDeck = numDeck;
		this->typeShip = typeShip;
		this->nameCategoryShip = nameCategoryShip;
		this->horizontal = horizontal;
	}
private:
	int numDeck;
	int typeShip;
	bool horizontal;
	string nameCategoryShip;
	int x;
	int y;
};

void printMap(Cell (*map)[length]) {
	cout << "   ";
	for (int j = 1; j <= length; j++) {
		cout << " " << j ;
	}

	cout << endl << "   _____________________" << endl;
	cout << "  |                     |" << endl;
	for (int i = 0; i < height; i++) {
		
		char letter = 'a' + i;

		cout << letter << " | ";

		for (int j = 0; j < length; j++) {
			cout<< map[i][j].isShip<<" ";
		}

		cout << "|" << endl;
	}
	cout << "  |_____________________|";
}

int main()
{
	srand(time(NULL));
	Cell map[height][length]; //двовимірний масив для прязки координат союзних кораблів на мапі
	Cell enemyMap[height][length]; //двовимірний масив для прязки координат ворожих кораблів на мапі
	map[1][1].isShip = 1;
	map[1][2].isShip = 1;
	map[1][3].isShip = 1;
	printMap(map);

}
