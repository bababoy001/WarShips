#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;


class Cell{
public:
	Cell() {

	}

};

class typeShip {
public:
	Ships(int typeShip, string nameCategoryShip) {
		this->typeShip = typeShip;
		this->nameCategoryShip = nameCategoryShip;
	}
private:
	int typeShip;
	string nameCategoryShip;
};

class Ships {
public:
	Ships(int numDeck, typeShip categoryShip, string nameShip) {
		this->numDeck = numDeck;
		this->categoryShip = categoryShip;
		this->nameShip = nameShip;
	}
private:
	int numDeck;
	typeShip categoryShip;
	string nameShip;
};

int main()
{
	srand(time(NULL));
	Cell Map[10][10] = { 0 }; //двовимірний масив для прязки координат союзних кораблів на мапі
	Cell enemyMap[10][10] = { 0 }; //двовимірний масив для прязки координат ворожих кораблів на мапі


}
