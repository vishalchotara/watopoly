#include "nonproperty.h"

class GooseNesting : public NonProperty {
public:
	GooseNesting();
	void playerEffect(std::shared_ptr<Player>);
};
