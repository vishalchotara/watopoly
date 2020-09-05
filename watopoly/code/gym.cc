#include "gym.h"
#include "exception.h"
#include <iostream>

Gym::Gym(std::string name, std::shared_ptr<MonopolyBlock> b) : Property(name, 150, b) {
	b->getMembers()->push_back(this);
}

int Gym::usageFees() {
	if (getBlock()->countOwner(getOwner()) == 2) {
		return 10 * (rand() % 6 + 1 + rand() % 6 + 1);
	}
	else return 4 * (rand() % 6 + 1 + rand() % 6 + 1);
}

void Gym::playerEffect(std::shared_ptr<Player> p) {
	if (getOwner() == nullptr) {
		if (p->getMoney() < getCost()) {
			std::cout << "You cannot purchase this because you do not have enough money!\n";
			throw Auction(*this);
		}
		else {
			std::string answer;
			std::cout << "Would you like to purchase " << getName() << " (Gym) for $" << getCost() << "?\n";
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
			p->withdrawMoney(usageFees());
			std::cout << "You pay $" << usageFees() << " to " << getOwner()->getName() << " in usage fees.\n";
			std::cout << "Your updated balance is $" << p->getMoney() << '\n';
			getOwner()->addMoney(usageFees());
		}catch(outOfMoney & out){
			out.playerowed = getOwner();
			throw(out);
		}
	}
}

void Gym::mortgageBy(Player * player){
	if(this->isMortgaged()){
		throw(Exception{"You have already mortaged the property."});
	}try{
		player->addMoney(this->getMortgage());
		this->setMortgaged();
	}catch(Exception & e){
		throw(e);
	}
}

void Gym::unmortgageBy(Player * player){
	if(!this->isMortgaged()){
		throw(Exception{"You have already unmortaged the property."});
	}else if(this->getMortgage() * 6 / 5 > player->getMoney()){
		throw(Exception{"You don't have enough money."});
	}try{
		player->withdrawMoney(this->getMortgage() * 6 / 5);
		this->setUnmortgaged();
	}catch(Exception & e){
		throw(e);
	}
}

int Gym::getImprovements() {
    throw Exception{"Error, this building cannot be improved."};
	return 0;
}

void Gym::setImprovements(int level) {}

void Gym::sellimprove(Player * player){
	throw(Exception{"This building cannot be improved"});
}

void Gym::improve(Player * player){
	throw(Exception{"This building cannot be improved"});
}
