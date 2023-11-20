#include "defoltShip.h"

defoltShip::defoltShip() : Ship() {}

defoltShip::defoltShip(int numDeck, bool horizontal) : Ship(numDeck, "defaultShip", horizontal) {}