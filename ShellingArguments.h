#pragma once

#include "IArguments.h"
#include "ShipManager.h"

struct ShellingArguments : public IArguments {
	ShellingArguments(ShipManager* ship_manager) :
		ship_manager(ship_manager) {};

	void accept(IVisitor& visitor) override {
		visitor.Visit(*this);
	}

	ShipManager* ship_manager;
};