#ifndef _SQUARE_
#define _SQUARE_

#include <vector>
#include <string>
#include "player.h"

class Player;


class Square {
	std::vector<Player*> currPlayers;
	std::string name;
public:
	Square(std::string);
	std::vector<Player*> getPlayers();
	std::string getName();
	virtual void playerEffect(std::shared_ptr<Player>) = 0;
};

#endif

