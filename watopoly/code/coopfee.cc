#include "coopfee.h"
#include <iostream>

CoopFee::CoopFee() : NonProperty("Co-op Fee")
{
}

void CoopFee::playerEffect(std::shared_ptr<Player> p)
{
	p->withdrawMoney(150);
	std::cout << "You pay $150 in co-op fees\n";
}
