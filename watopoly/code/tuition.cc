#include "tuition.h"
#include <iostream>

Tuition::Tuition() : NonProperty("Tuition") {}

void Tuition::playerEffect(std::shared_ptr<Player> p) {
	std::string answer;
	std::cout << "Would you like to pay (a) $300 or (b) 10% of your total worth? ";
	while (1) {
		std::cin >> answer;
		if (answer == "a") {
			p->withdrawMoney(300);
			std::cout << "You pay $300 to the bank, you balance is now $" << p->getMoney() << '\n';
			break;
		}
		else if (answer == "b") {
			p->withdrawMoney(p->worth() / 10);
			std::cout << "You pay $300 to the bank, you balance is now $" << p->worth() / 10 << '\n';
			break;
		}
		else {
			std::cout << "Invalid answer. Please enter either 'a' or 'b': ";
		}
	}
}
