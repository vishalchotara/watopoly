#include "property.h"

Property::Property(std::string& name, int c, std::shared_ptr<MonopolyBlock> b) :
    Square(name),
    cost{ c },
    mortgage{ c / 2 },
    block{ b }
{}

int Property::getCost() {
    return cost;
}

std::shared_ptr<Player> Property::getOwner() {
    return owner;
}

void Property::setOwner(std::shared_ptr<Player> newowner) {
    owner = newowner;
}

std::shared_ptr<MonopolyBlock> Property::getBlock()
{
    return block;
}

int Property::getMortgage() {
    return mortgage;
}

bool Property::isMortgaged(){
	return mortgaged;
}

void Property::setMortgaged(){
	mortgaged = true;
}

void Property::setUnmortgaged(){
	mortgaged = false;
}
