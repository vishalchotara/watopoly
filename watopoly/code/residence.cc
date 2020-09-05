#include "residence.h"
#include <iostream>
#include "exception.h"

Residence::Residence(std::string name, std::shared_ptr<MonopolyBlock> b) : Property(name, 200, b) {
	b->getMembers()->push_back(this);
}

int Residence::getRent() {
    return rent[getBlock()->countOwner(getOwner()) - 1];
}

void Residence::playerEffect(std::shared_ptr<Player> p) {
	if (getOwner() == nullptr) {
		std::string answer;
		if (p->getMoney() < getCost()) {
			std::cout << "You cannot purchase this because you do not have enough money!\n";
			throw Auction(*this);
		}
		else {
			std::cout << "Would you like to purchase " << getName() << " (Residence) for $" << getCost() << "?\n";
			while (1) {
				std::cin >> answer;
				if (answer == "yes") {
					p->withdrawMoney(this->getCost());
					this->setOwner(p);
					p->addToWorth(getCost());
					std::cout << "You now own " << getName() << ", your updated balance is $" << p->getMoney() << '\n';
					break;
				}
				else if (answer == "no") {
					throw Auction(*this);
					break;
				}
				else {
					std::cout << "Invalid input. Please enter either 'yes' or 'no':";
				}
			}
		}
	}
	else if (getOwner()->getName() == p->getName()) std::cout << "You own this property. Welcome home :)\n";
	else {
		if(this->isMortgaged()){
			return;
		}try{
			p->withdrawMoney(getRent());
			std::cout << "You pay $" << getRent() << " to " << getOwner()->getName() << " in rent.\n";
			std::cout << "Your updated balance is $" << p->getMoney() << '\n';
			getOwner()->addMoney(getRent());
		}catch(outOfMoney & out){
			out.playerowed = getOwner();
			throw(out);
		}
	}
}

void Residence::mortgageBy(Player * player){
	if(this->isMortgaged()){
		throw(Exception{"You have already mortgaged the property."});
	}try{
		player->addMoney(this->getMortgage());
		this->setMortgaged();
	}catch(Exception & e){
		throw(e);
	}
}

void Residence::unmortgageBy(Player * player){
	if(!this->isMortgaged()){
		throw(Exception{"You have already unmortgaged the property."});
	}else if(this->getMortgage() * 6 / 5 > player->getMoney()){
		throw(Exception{"You don't have enough money."});
	}try{
		player->withdrawMoney(this->getMortgage() * 6 / 5);
		this->setUnmortgaged();
	}catch(Exception & e){
		throw(e);
	}
}

int Residence::getImprovements() {
    throw Exception{"Error, this building cannot be improved."};
	return 0;
}

void Residence::setImprovements(int level) {}

void Residence::sellimprove(Player * player){
	throw(Exception{"This building cannot be improved"});
}

void Residence::improve(Player * player){
	throw(Exception{"This building cannot be improved"});
}
