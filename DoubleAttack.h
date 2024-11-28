#pragma once

#include "IAbility.h"

class DoubleAttack : public IAbility{
public:
	DoubleAttack(GameField* field);

	void applyAbility();

private:
	GameField* field;
};