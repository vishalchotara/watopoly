#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include <memory>

class Property;
class Residence;
class Upgradable;
class Gym;

class Player {
	std::string name;
	char piece;
	int pos = 0;
	int money = 1500;
	int cups = 0;
	bool tims = false;
	int turnsInTims = 0;
	int netWorth = 0;
public:
	Player(std::string& name, char piece);
	std::string getName();
	char getPiece();

	int getPos();
	void setPos(int);

	int getMoney();
	void withdrawMoney(int);
	void addMoney(int);

	int getCups();
	void addCup();
	void useCup();
	void setInTims(bool);
	bool inTims();
	int turnsinTims();
	void resetTims();
	void stayinTims();

	int worth();
	void addToWorth(int worth);

	void buyImprovement(Property * up); // player improves 'up'
	void sellImprovement(Property * up); // player sell improvement of 'up'
	void getMortgage(Property * p); // mortage a building
	void getUnmortgage(Property * p); // unmortage a building 
};

class outOfMoney {
public:
	std::shared_ptr<Player> playerowed = nullptr;
	int amountowed = 0;
	outOfMoney(std::shared_ptr<Player> p, int i) : playerowed{ p }, amountowed{ i } {}
};

#endif
