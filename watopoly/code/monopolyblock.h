#ifndef _MONOPOLYBLOCK_
#define _MONOPOLYBLOCK_


#include <vector>
#include <memory>
#include "player.h"
#include "property.h"

class Property;

class MonopolyBlock {
	std::vector<Property*> members;
public:
	MonopolyBlock() {}
	int countOwner(std::shared_ptr<Player>);
	std::vector<Property*> * getMembers();
};

#endif

