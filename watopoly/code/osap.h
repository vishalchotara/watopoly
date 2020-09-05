
#include "nonproperty.h"

class OSAP : public NonProperty {
public:
	OSAP();
	void playerEffect(std::shared_ptr<Player>) override;
};
