#pragma once
#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"

struct Player{
	GameField field;
	ShipManager ship_manager;
	AbilityManager ability_manager;
	bool double_attack = false;

	Player(GameField& field, ShipManager& ship_manager, AbilityManager& ability_manager, bool double_attack)
		: field(field), ship_manager(ship_manager), ability_manager(ability_manager), double_attack(double_attack) {}
	
	~Player() = default;
};