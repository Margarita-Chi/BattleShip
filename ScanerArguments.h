#pragma once

#include "GameField.h"
#include "IArguments.h"

struct ScanerArguments : public IArguments {
	ScanerArguments(Coords coordinates, GameField* field) :
		coords(coordinates),
		field(field) {};

	void accept(IVisitor& visitor) override {
		visitor.Visit(*this);
	}

	Coords coords;
	GameField* field;
};