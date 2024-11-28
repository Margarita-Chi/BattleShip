#pragma once
#include "ShipManager.h"
#include "GameField.h"

class IAbility {
public:
	virtual void applyAbility() = 0;
};