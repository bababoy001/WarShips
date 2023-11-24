#include "Print.h"
#include <cstdlib>
using namespace std;
void Print::lvlChoice(int& lvl) {
    cout << "Enter lvl of bot (1-2): ";
    cin >> lvl;
}

void Print::sizeMap(int& height, int& length) {
    cout << "Enter height map: ";
    cin >> height;
    cout << "Enter length map: ";
    cin >> length;
}

void Print::printMap(vector<vector<Cell>>& currentMap, int height, int length) {
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

void Print::printSentence(string sentence) {
    cout << endl << sentence << endl;
}

void Print::cinCoord(int& x, int& y) {
	char letter;
	int number;
    cin >> number >> letter;
	x = number - 1;
	y = letter - 'a';
}

void Print::printAllMaps(vector<vector<Cell>>& map, vector<vector<Cell>>& enemyMap, int height, int length) {
	
	printSentence("Your Map:");
	printMap(map, height, length);

	printSentence("Enemy's Map:");
	printMap(enemyMap, height, length);
}

void Print::numberOfUniqueShips(int max_unique, int& fuel, int& zalp) {
	cout << "You have " << max_unique << " unique Ships, enter number of fuel ships (the remainder will be salvo ships): ";
	cin >> fuel;
	zalp = max_unique - fuel;
}

void Print::createShip(int& temp_size_ship, bool& horizontal, int currnt, int max_deck, int max_length_ship) {
	cout << "!(Available " << max_deck - currnt << " decks, maximum length of the ship " << max_length_ship << " )!";
	cout << endl <<"Enter size of ship : ";
	cin >> temp_size_ship;
	if (((temp_size_ship + currnt) > max_deck) || temp_size_ship > max_length_ship){
		cout << endl << "Wrong size, try again.";
		temp_size_ship = 1;
		return createShip(temp_size_ship, horizontal, currnt, max_deck, max_length_ship);
	}
	isShipHorizonal(horizontal);
}

void Print::isShipHorizonal(bool& horizontal) {
	cout << endl << "Enter '1' if you want a horizontal ship and '0' if vertical : ";
	cin >> horizontal;
}

void Print::placeShip(bool& random) {
	cout << endl << "Enter '1' if you want the ship in a random location and '0' if you want to set it manually : ";
	cin >> random;
}
