#pragma once
#include <iostream>
#include <vector>
#include "Coords.h"

class Ship {
public:
	struct ShipSegment {
		enum Status {
			unharmed,
			damaged,
			destroyed
		};
		Coords coords;
		Status status = unharmed;
		Ship* ship_pointer = nullptr;
	};

	enum Orientation {
		Vertical,
		Horizontal,
		Unknown
	};

	Ship();

	Ship(int size);

	Ship(const Ship& other);

	Ship(Ship&& other) noexcept;

	~Ship();

	int getSize() const;

	int getMaxHealth() const;

	int getCurrentHealth() const;

	Ship::Orientation getOrientation() const;

	bool isUnharmed();

	bool isDestroyed();

	void addToField(Ship::Orientation orientation, Coords new_top_left);

	void attackSegment(ShipSegment* segment);

	void print_info();

	ShipSegment* getSegmentByIndex(int index);

private:
	int size;
	Orientation orientation;
	Coords top_left;
	int max_health;
	int health;
	std::vector<ShipSegment> segments;
};