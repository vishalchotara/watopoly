#include "gototims.h"
#include <iostream>

GoToTims::GoToTims() : NonProperty("Go To Tims")
{
}

void GoToTims::playerEffect(std::shared_ptr<Player> p) {
	p->setPos(10);
	p->setInTims(true);
	std::cout << "You get stuck in the DC Tim's Line!\n";
}
