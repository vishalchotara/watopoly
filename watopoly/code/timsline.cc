#include "timsline.h"
#include <iostream>

TimsLine::TimsLine() : NonProperty("DC Tim's Line") {}

void TimsLine::playerEffect(std::shared_ptr<Player> p) {
	std::cout << "The line is short and you get your coffee quickly\n";
}
