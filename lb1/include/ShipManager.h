#pragma once
#include "GameField.h"


class ShipManager {
private:
	std::vector<Ship*> free_ships;
	std::vector<Ship*> active_ships;

public:
	ShipManager();

	ShipManager(std::vector<int> sizes);

	ShipManager(const ShipManager& other);

	ShipManager(ShipManager&& other) noexcept;

	~ShipManager();

	int getAliveShipsCount();
	
	int getDetroyedShipsCount();

	int getShipCount();

	int getFreeShipCount();

	void addShipToField(GameField& field, int index, Coords new_coord, Ship::Orientation orientation);
};