#ifndef _GYM_
#define _GYM_

#include "property.h"
#include <random>

class Gym : public Property {

public:
	Gym(std::string name, std::shared_ptr<MonopolyBlock> b);
	int usageFees();
	void playerEffect(std::shared_ptr<Player>);
	void mortgageBy(Player * player) override;
	void unmortgageBy(Player * player) override;
	int getImprovements() override;
	void setImprovements(int level) override;
	void sellimprove(Player * player) override;
	void improve(Player * player) override;
};

#endif

