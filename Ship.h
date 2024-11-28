#pragma once
#include <iostream>
#include <vector>
#include "Coords.h"

class Ship {
public:
	class ShipSegment {
	public:
		enum Status {
			unharmed,
			damaged,
			destroyed
		};

		ShipSegment(int index, Ship* ship_ptr);

		bool attack();

		Status getStatus() const;

	private:
		int index;
		Status status;
		Ship* ship_pointer;
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

	void attack();

	void print_info();

	Ship::ShipSegment& getSegmentByIndex(int index);

private:
	int size;
	Orientation orientation;
	Coords top_left;
	int max_health;
	int health;
	std::vector<ShipSegment> segments;
};