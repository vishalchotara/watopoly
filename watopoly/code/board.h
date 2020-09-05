#ifndef _BOARD_
#define _BOARD_

#include <vector>
#include <memory>
#include <iostream>
#include "square.h"
#include "property.h"
#include "upgradable.h"
#include "residence.h"
#include "gym.h"
#include "slc.h"
#include "nh.h"
#include "osap.h"
#include "tuition.h"
#include "timsline.h"
#include "goosenesting.h"
#include "gototims.h"
#include "coopfee.h"

class Square;

class Board {
	friend std::istream& operator>>(std::istream& in, Board &b);
	friend std::ostream& operator<<(std::ostream& out, Board &b);
	std::vector<std::shared_ptr<Square>> squares;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Property>> properties;
	int currplayer = 0;
	int numplayers = 0;
	int totalcups = 0;
public:
	//Board();
	void newBoard(std::vector<std::shared_ptr<Player>> &p);
	void setPlayers(std::vector<std::shared_ptr<Player>> &p);
	void move(int i); // currplayer rolls dice, moves squares, and as the effect of the square applied on them
	std::string peek(int); // returns the name of the square at i
	std::shared_ptr<Player> currentPlayer();
	std::vector<std::shared_ptr<Player>> allPlayers();
	void endturn();
	std::shared_ptr<Square> getSquare(int i);
	void addCup();
	void useCup();
	int getCups();
	// if trade() return false, ask p1 if he wants to trade again
	void trade(const std::string &from, const std::string &to, const std::string &give, const std::string &receive); 
	void printAssets(std::shared_ptr<Player> p); // prints assets of current player
	std::vector<std::string> getAssets(std::shared_ptr<Player> p);
	void getAllAssets();
	void startAuction(Property*);
	void transferAssets(std::shared_ptr<Player> from, std::shared_ptr<Player> to);
	void dropout(); // current player drops out
	std::shared_ptr<Property> findProperty(std::string prop_name); //find property with a given name
	char getPiece(std::string &c);
};

std::istream& operator>>(std::istream& in, Board &b);
std::ostream& operator<<(std::ostream& out, Board &b);

void displayBoard(Board &b);

std::string firstline_print(std::shared_ptr<NonProperty> np); // Name print
std::string firstline_print(std::shared_ptr<Upgradable> up); //improvement print
std::string firstline_print(std::shared_ptr<Residence> res); // Name print
std::string firstline_print(std::shared_ptr<Gym> gym); // Name print

std::string secondline_print(std::shared_ptr<NonProperty> np); // Name print
std::string secondline_print(std::shared_ptr<Upgradable> up); //'-' print
std::string secondline_print(std::shared_ptr<Residence> res); // space print
std::string secondline_print(std::shared_ptr<Gym> gym); // space print

std::string thirdline_print(std::shared_ptr<Square> sq); // space print
std::string thirdline_print(std::shared_ptr<Upgradable> up); // name print

std::string fourthline_print(std::shared_ptr<Square> sq, Board & b); // space print

std::string mult_string(std::string s, int n);

void displayStrip(Board &b, Player *player);
#endif
