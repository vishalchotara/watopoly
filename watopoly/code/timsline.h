#include "nonproperty.h"
#include <memory>

class TimsLine : public NonProperty {
public:
	TimsLine();
	void playerEffect(std::shared_ptr<Player>);
};

