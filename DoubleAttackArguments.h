#pragma once

#include "GameField.h"
#include "IArguments.h"

struct DoubleAttackArguments : public IArguments {
	DoubleAttackArguments(GameField* field) :
		field(field) {};

	void accept(IVisitor& visitor) override {
		visitor.Visit(*this);
	}

	GameField* field;
};