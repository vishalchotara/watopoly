
#include "nonproperty.h"
#include "player.h"

class Tuition : public NonProperty {
public:
	Tuition();
	void playerEffect(std::shared_ptr<Player>);
};


