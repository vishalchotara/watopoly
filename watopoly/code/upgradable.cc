#include "upgradable.h"
#include <iostream>
#include "exception.h"
#include <algorithm>

Upgradable::Upgradable(std::string name, int c, int ic, int t0, int t1, int t2, int t3, int t4, int t5, std::shared_ptr<MonopolyBlock> b) :
    Property(name, c, b),
    improvementCost{ ic },
    tuition{ t0, t1, t2, t3, t4, t5 } {
	b->getMembers()->push_back(this);
}

int Upgradable::getImprovementCost() {
    return improvementCost;
}

int Upgradable::getImprovements() {
    return improvements;
}

void Upgradable::setImprovements(int level) {
	improvements = level;
}

int Upgradable::getTuition() {
    if (ownMonopoly() && getImprovements() == 0) return 2 * tuition[0];
    return tuition[improvements];
}

void Upgradable::playerEffect(std::shared_ptr<Player> p) {
	if (getOwner() == nullptr) {
		if (p->getMoney() < getCost()) {
			std::cout << "You cannot purchase this because you do not have enough money!\n";
			throw Auction(*this);
		}
		else {
			std::string answer;
			std::cout << "Would you like to purchase " << getName() << " (Academic Building) for $" << getCost() << "?\n";
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
			p->withdrawMoney(getTuition());
			std::cout << "You pay $" << getTuition() << " to " << getOwner()->getName() << " in tuition.\n";
			std::cout << "Your updated balance is $" << p->getMoney() << '\n';
			getOwner()->addMoney(getTuition());
		}catch(outOfMoney & out){
			out.playerowed = getOwner();
			throw(out);
		}
	}
}

//returns true if the owener of the upgradable forms a monopoly and false otherwise
bool Upgradable::ownMonopoly(){
	return getBlock()->countOwner(getOwner()) == getBlock()->getMembers()->size();
}

//imporve the building
void Upgradable::improve(Player * player){
	if(this->getOwner() == nullptr || player->getName() != this->getOwner()->getName()){
		throw(Exception{"This building is not yours :("}); // not ur property
	}else if(this->isMortgaged()){
		throw(Exception{"You have mortgaged this building."});
	}else if(!this->ownMonopoly()){
		throw(Exception{"You do not own the monopoly, keep tring!"}); // does not own monopoly
	}else if(improvements == 5){ // improvement number is at max
		throw(Exception{"You have reached the maximum improvement number."});
	}else if(improvementCost > player->getMoney()){
		throw(Exception{"You don't have enough money."});
	}else{ // buy improvement
		try{
			player->withdrawMoney(improvementCost);
			improvements += 1;
		}catch(Exception & e){
			throw(e);
		}
	}
}
void Upgradable::sellimprove(Player * player){
	if(this->getOwner() == nullptr || player->getName() != this->getOwner()->getName()){
		throw(Exception{"This building is not yours :("}); // not ur property
	}else if(this->isMortgaged()){
		throw(Exception{"You have mortgaged this building."});
	}else if(improvements == 0){
		throw(Exception{"You do not have enough improvements to sell"}); //no improvement
	}else{
		try{
			player->addMoney(improvementCost);
			improvements -= 1;
		}catch(Exception & e){
			throw(e);
		}
	}
}

void Upgradable::mortgageBy(Player * player){
	if(this->isMortgaged()){
		throw(Exception{"You have already mortgaged the property."});
	}else if(improvements != 0){
		throw(Exception{"You need to sale all the improvements."});
	}try{
		player->addMoney(this->getMortgage());
		this->setMortgaged();
	}catch(Exception & e){
		throw(e);
	}
}

void Upgradable::unmortgageBy(Player * player){
	if(!this->isMortgaged()){
		throw(Exception{"You have already unmortgaged the property."});
	}else if(this->getMortgage() * 6 / 5 > player->getMoney()){
		throw(Exception{"You don't have enough money."});
	}try{
		player->withdrawMoney(this->getMortgage() * 6 / 5);
		this->setUnmortgaged();
		if(improvements < 0){
			improvements = 0;
		}
	}catch(Exception & e){
		throw(e);
	}
}
