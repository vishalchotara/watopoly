#ifndef _PROPERTY_
#define _PROPERTY_

#include <memory>
#include "player.h"
#include "square.h"
#include "monopolyblock.h"

class Player;
class Square;
class MonopolyBlock;

class Property : public Square {
	int cost;
	std::shared_ptr<Player> owner = nullptr;
	bool mortgaged= false;
	int mortgage;
	std::shared_ptr<MonopolyBlock> block;
public:
	Property(std::string& name, int c, std::shared_ptr<MonopolyBlock> b);
	int getCost();
	std::shared_ptr<Player> getOwner();
	void setOwner(std::shared_ptr<Player>);
	std::shared_ptr<MonopolyBlock> getBlock();
	int getMortgage();
	virtual void playerEffect(std::shared_ptr<Player>) = 0;
	bool isMortgaged();
	void setMortgaged();
	void setUnmortgaged();
	virtual void mortgageBy(Player * player) = 0; // property mortaged by player
	virtual void unmortgageBy(Player * player) = 0; // property unmortaged by plater
	virtual int getImprovements() = 0;
	virtual void setImprovements(int level) = 0;
	virtual void improve(Player * player) = 0;
	virtual void sellimprove(Player * player) = 0; // player sell improvement of this building
};

class Auction {
public:
	Property* p;
	Auction(Property& prop) : p{ &prop } {}
};

#endif

