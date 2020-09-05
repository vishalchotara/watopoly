#include "nonproperty.h"
#include "player.h"

class GoToTims : public NonProperty {
public:
	GoToTims();
	void playerEffect(std::shared_ptr<Player>);
};
