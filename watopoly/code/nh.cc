#include "nh.h"
#include <iostream>

NH::NH(Board &b) : NonProperty("NH"), board{ &b } {}

void NH::playerEffect(std::shared_ptr<Player> p) {
	int m = rand() % 100;
	if (m == 0 && board->getCups() < 4) {
		std::cout << "You get a Roll Up the Rim cup!\n";
		p->addCup();
		board->addCup();
	}
	else {
		int n = rand() % 18;
		if (0 == n) { // -200
			std::cout << "You lose $200!\n";
			p->withdrawMoney(200);
		}
		else if (1 <= n && n <= 2) { // -100
			std::cout << "You lose $100!\n";
			p->withdrawMoney(100);
		}//
		else if (3 <= n && n <= 5) { // -50
			std::cout << "You lose $50!\n";
			p->withdrawMoney(50);
		}
		else if (6 <= n && 11 <= 11) { // 25
			std::cout << "You gain $25!\n";
			p->addMoney(25);
		}
		else if (12 <= n && n <= 14) { // 50
			std::cout << "You gain $50!\n";
			p->addMoney(50);
		}
		else if (15 <= n && n <= 16) { // 100
			std::cout << "You gain $100!\n";
			p->addMoney(100);
		}
		else { // 200
			std::cout << "You gain $200!\n";
			p->addMoney(200);
		}
	}
}
