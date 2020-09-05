#ifndef _NH_
#define _NH_

#include "nonproperty.h"
#include "player.h"
#include "board.h"

class Board;

class NH : public NonProperty {
	Board* board;
public:
	NH(Board& b);
	void playerEffect(std::shared_ptr<Player>) override;
};

#endif
