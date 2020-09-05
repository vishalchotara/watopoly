#include "nonproperty.h"
#include "player.h"

class CoopFee : public NonProperty {
public:
	CoopFee();
	void playerEffect(std::shared_ptr<Player>);
};
