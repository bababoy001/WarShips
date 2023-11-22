#include "defoltShip.h"
using namespace std;
defoltShip::defoltShip() : Ship() {}

defoltShip::defoltShip(int numDeck, bool horizontal) : Ship(numDeck, "defaultShip", horizontal) {}