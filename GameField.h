#pragma once
#include "Cell.h"
#include "ShipPlacementExeption.h"
#include "AttackOutOfFieldExeption.h"

class GameField{
private:
	int width;
	int height;
	Cell** field;

	bool double_attack; //временное решение, пока не появвится плеер

	bool isShipCoordsOk(Coords top_left, Ship::Orientation orientation, int size) const;

public:
	GameField(int width, int height);

	GameField(const GameField& other);

	GameField(GameField&& other) noexcept;

	~GameField();

	int getWidth() const;

	int getHeight() const;
	
	bool isCoordsInField(Coords coords_check) const;

	void setDoubleAttack();

	void addShip(Ship& ship, Coords top_left, Ship::Orientation orientation); 

	bool attack(Coords attack_coords);

	void setCellStatus(Coords coords, Cell::status status);

	Cell::status getCellStatus(Coords coords);

	bool isShipHereDestroyed(Coords coords);

	bool isShipHere(Coords coords);

	void print_field();

	void print_field_ver_ox();
};