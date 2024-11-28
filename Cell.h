#pragma once
#include "Ship.h"

struct Cell {
	enum status {
		unknown,
		empty,
		ship
	};
	bool ship_is_here = false;
	bool ship_is_nearby = false;
	status status_cell = unknown;
	Ship::ShipSegment* ship_segment_pointer = nullptr;
};