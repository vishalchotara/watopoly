#include "goosenesting.h"
#include <iostream>

GooseNesting::GooseNesting() : NonProperty("Goose Nesting") {}

void GooseNesting::playerEffect(std::shared_ptr<Player>)
{
	std::cout << "You walk around the geese cautiously to avoid angering them\n";
}
