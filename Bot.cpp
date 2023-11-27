#include "Bot.h"
using namespace std;
pair<int, int> Bot::attack(bool& playerTurn, vector<vector<Cell>>& currentMap, int height, int length, int currntPlayerShips, vector<pair<int, int>>& mines, pair<int, int >& pairHitedBoards) {
	int x;
	int y;

	botShoot(height, length, x, y);

	if (currentMap[x][y].isHit || currentMap[x][y].isMiss) {
		printAll.printSentence("This cell already hitted");
		return attack(playerTurn, currentMap, height, length, currntPlayerShips, mines, pairHitedBoards);
	}

	if (currentMap[x][y].isMine) {
		currentMap[x][y].isHit = 1;
		playerTurn = !playerTurn;
		return make_pair(x, y);
	}

	else if (!currentMap[x][y].isHit && !currentMap[x][y].isMiss && !currentMap[x][y].isShip) {
		currentMap[x][y].isMiss = 1;
		playerTurn = !playerTurn;
		return make_pair(-1, -1);
	}
	else if (currentMap[x][y].isShip && !currentMap[x][y].isHit) {
		currentMap[x][y].isHit = 1;
		return make_pair(x, y);
	}
}

void Bot::botShoot(int height, int length, int& x, int& y) {
	x = rand() % height;
	y = rand() % length;
}
