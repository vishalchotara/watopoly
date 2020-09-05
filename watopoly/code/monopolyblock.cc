#include "monopolyblock.h"

int MonopolyBlock::countOwner(std::shared_ptr<Player> p)
{
    int ret = 0;
    for (std::vector<Property*>::iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->getOwner()!= nullptr && !(*it)->isMortgaged() && (*it)->getOwner()->getName() == p->getName()) ++ret;
    }
    return ret;
}

std::vector<Property*> * MonopolyBlock::getMembers() {
    return &members;
}
