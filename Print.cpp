#include "Print.h"
#include <cstdlib>

void Print::lvlChoice(int& lvl) {
    std::cout << "Enter lvl of bot (1-2): ";
    std::cin >> lvl;
}

void Print::sizeMap(int& height, int& length) {
    std::cout << "Enter height map: ";
    std::cin >> height;
    std::cout << "Enter length map: ";
    std::cin >> length;
}

void Print::printMap(std::vector<std::vector<Cell>>& currentMap, int height, int length) {
	std::cout << "   ";
	for (int j = 0; j < length; j++) {
		char letter = 'a' + j;
		std::cout << " " << letter;
	}
	std::cout << std::endl << "   ";
	for (int j = 0; j <= length * 2; j++) {
		std::cout << "_";
	}
	std::cout << std::endl;


	for (int i = 0; i < height; i++) {
		if (i < 9) {
			std::cout << i + 1 << " | ";
		}
		else {
			std::cout << i + 1 << "| ";
		}
		for (int j = 0; j < length; j++) {
			if (currentMap[i][j].isShip) {
				if (currentMap[i][j].isHit) {
					std::cout << "X ";
					continue;
				}
				std::cout << currentMap[i][j].symbol << " ";
			}
			else if (currentMap[i][j].isMiss) {
				std::cout << "* ";
			}
			else {
				std::cout << "  ";
			}
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "  |";
	for (int j = 0; j <= length * 2; j++) {
		std::cout << "_";
	}
	std::cout << "|" << std::endl;
}

void Print::printSentence(std::string sentence) {
    std::cout << std::endl << sentence << std::endl;
}

void Print::cinCoord(int& number, char& letter) {
    std::cin >> number >> letter;
}

void Print::printAllMaps(std::vector<std::vector<Cell>>& map, std::vector<std::vector<Cell>>& enemyMap, int height, int length) {
	system("cls");
	printSentence("Your Map:");
	printMap(map, height, length);

	printSentence("Enemy's Map:");
	printMap(enemyMap, height, length);
}