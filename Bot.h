#pragma once
#include "ShipManager.h"
#include "GameField.h"
#include <vector>

class Bot {
public:
	Bot(); //10*10, 10 кораблей

	Bot(std::vector<int> size_ships, int width, int height);

	Bot(ShipManager* ship_manager, GameField* field);

	~Bot();

	void shipGenerate(ShipManager* ship_manager);

	GameField* field;
	ShipManager* ship_manager;
};