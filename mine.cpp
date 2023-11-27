#include "mine.h"
using namespace std;
mine::mine() {}


void mine::PlaceMine(mine* mine_temp, vector<vector<Cell>>& currentMap, int height, int length, bool random) {
	bool wrongPlace;
	int x;
	int y;
	do {
		wrongPlace = 0;
		if (!random) {
			printAll.printSentence("!()!");
			printAll.printSentence("Enter coordinates for place a Mine (number letter): ");
			printAll.cinCoord(x, y);
		}
		else if (random) {
			x = rand() % height;
			y = rand() % length;	
		}

		if (!check.isCellForShip(currentMap, x, y, height, length)) {
			wrongPlace = 1;
			printAll.printSentence("Wrong coordinates for place a Mine, try again. ");
		}
		else {
			pair<int, int> pairXY = make_pair(x, y);
			mine_temp->coordinatesMine = pairXY;
		}
	} while (wrongPlace);

	currentMap[mine_temp->coordinatesMine.first][mine_temp->coordinatesMine.second].symbol = 'M';
	currentMap[mine_temp->coordinatesMine.first][mine_temp->coordinatesMine.second].isMine = 1;
}
