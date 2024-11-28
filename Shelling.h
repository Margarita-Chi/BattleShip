#pragma once
#include "IAbility.h"


class Shelling : public IAbility{
public:
	Shelling(ShipManager* ship_manager);

	void applyAbility();

private:
	ShipManager* ship_manager;
};

