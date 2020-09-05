#ifndef _SLC_
#define _SLC_

#include "nonproperty.h"
#include "player.h"
#include "board.h"

class Board;

class SLC : public NonProperty {
	Board* b;
public:
	SLC(Board& b);
	void playerEffect(std::shared_ptr<Player>) override;
};

#endif
