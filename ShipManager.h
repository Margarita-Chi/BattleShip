#pragma once
#include "Ship.h"


class ShipManager {
private:
	std::vector<std::pair<Ship*, bool>> ships;

public:
	ShipManager();

	ShipManager(std::vector<int> sizes);

	ShipManager(const ShipManager& other);

	ShipManager(ShipManager&& other) noexcept;

	~ShipManager();

	int getDetroyedShipsCount();

	std::vector<Ship*> getAliveShips();
	
	int getShipCount();

	int getFreeShipCount();

	std::vector<int> getShipSizes();

	Ship& getShip(int index);
};