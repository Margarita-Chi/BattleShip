#pragma once
#include "IAbility.h"


class Scaner : public IAbility{
public:
	Scaner(Coords coords, GameField* field);

	void applyAbility();

private:
	Coords coords;
	GameField* field;
};

