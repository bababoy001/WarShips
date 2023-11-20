#include "Bot.h"

std::pair<int, int> Bot::attack(bool& playerTurn, std::vector<std::vector<Cell>>& currentMap, int height, int length, int currntPlayerShips) {
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
		return std::make_pair(-1, -1);
	}
	if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
		currentMap[x][y].isHit = 1;
		return std::make_pair(x, y);
	}
}

void Bot::botShoot(int height, int length, int& x, int& y) {
	x = rand() % height;
	y = rand() % length;
}
