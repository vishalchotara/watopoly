#include "player.h"
#include <iostream>
#include "exception.h"
#include "property.h"
#include "upgradable.h"

Player::Player(std::string& name, char piece) {
	this->name = name;
	this->piece = piece;
}

std::string Player::getName() { return name; }

char Player::getPiece() { return piece; }

int Player::getPos() { return pos; }

void Player::setPos(int i) { pos = i; }

int Player::getMoney() { return money; }

void Player::withdrawMoney(int i) {
	if (i > money) {
		throw outOfMoney(nullptr, i - money);
	}
	money -= i;
}

void Player::addMoney(int i) { money += i; }

int Player::getCups() { return cups; }

void Player::addCup() { ++cups; }

void Player::useCup()
{
	--cups;
}

int Player::worth() {
	return netWorth;
}

void Player::addToWorth(int worth) {
	netWorth += worth;
}

void Player::setInTims(bool b) {
	tims = b;
}

bool Player::inTims()
{
	return tims;
}

int Player::turnsinTims()
{
	return turnsInTims;
}

void Player::resetTims()
{
	turnsInTims = 0;
	tims = false;
}

void Player::stayinTims()
{
	++turnsInTims;
}

void Player::buyImprovement(Property * up){
	try{
		up->improve(this);
	}catch(Exception & e){
		throw(e);
	}
}

void Player::sellImprovement(Property * up){
	try{
		up->sellimprove(this);
	}catch(Exception & e){
		throw(e);
	}
} // player sell improvement of 'up'

void Player::getMortgage(Property * p){
	if(p->getOwner().get() != this){
		throw(Exception{"You are not the owner of this property."});
	}try{
		p->mortgageBy(this);
	}catch(Exception & e){
		throw e;
	}
}

void Player::getUnmortgage(Property * p){
	if(p->getOwner().get() != this){
		throw(Exception{"You are not the owner of this property."});
	}try{
		p->unmortgageBy(this);
	}catch(Exception & e){
		throw e;
	}
}

