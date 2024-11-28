#pragma once
#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"

struct Player{
	GameField* field;
	ShipManager* ship_manager;
	AbilityManager* ability_manager;
	bool double_attack = false;
};