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

void Print::cinCoord(int& number, char& letter) {
    cin >> number >> letter;
}

void Print::printAllMaps(vector<vector<Cell>>& map, vector<vector<Cell>>& enemyMap, int height, int length) {
	system("cls");
	printSentence("Your Map:");
	printMap(map, height, length);

	printSentence("Enemy's Map:");
	printMap(enemyMap, height, length);
}