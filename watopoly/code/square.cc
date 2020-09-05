#include "square.h"

Square::Square(std::string n) {
	name = n;
}

std::vector<Player*> Square::getPlayers() {
	return currPlayers;
}

std::string Square::getName() {
	return name;
}
