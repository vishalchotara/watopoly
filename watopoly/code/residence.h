#ifndef _RESIDENCE_
#define _RESIDENCE_

#include "property.h"
#include <vector>
#include <string>

class Residence : public Property {
	int rent[4] = { 25, 50, 100, 200 };
public:
	Residence(std::string name, std::shared_ptr<MonopolyBlock> b);
	int getRent();
	void playerEffect(std::shared_ptr<Player>);
	void mortgageBy(Player * player) override;
	void unmortgageBy(Player * player) override;
	int getImprovements() override;
	void setImprovements(int level) override;
	void sellimprove(Player * player) override;
	void improve(Player * player) override;
};

#endif

