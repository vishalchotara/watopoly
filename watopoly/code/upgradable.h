#ifndef _UPGRADABLE_
#define _UPGRADABLE_

#include "property.h"
#include <memory>
#include <vector>
#include "monopolyblock.h"

class Upgradable : public Property {
	int improvementCost;
	int tuition[6];
	int improvements = 0;
	std::shared_ptr<Player> owner = nullptr;
public:
	//constructor
	Upgradable(std::string name, int c, int ic, int t0, int t1, int t2, int t3, int t4, int t5, std::shared_ptr<MonopolyBlock> b);
	//return the cost for the next improvement
	int getImprovementCost();
	//returns the number of improvements
	int getImprovements() override;
	void setImprovements(int level) override;
	//returns the tuition needs to be paid
	int getTuition();
	//returns true if the owener of the upgradable forms a monopoly and false otherwise
	bool ownMonopoly();
	//imporve the building
	void improve(Player * player) override;
	void playerEffect(std::shared_ptr<Player>) override;
	void mortgageBy(Player * player) override;
	void unmortgageBy(Player * player) override; 
	void sellimprove(Player * player) override;
};

#endif

