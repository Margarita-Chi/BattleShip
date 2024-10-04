#pragma once
#include "Cell.h"

class GameField{
private:
	int width;
	int height;
	Cell** field;

public:
	GameField();

	GameField(int width, int height);

	GameField(const GameField& other);

	GameField(GameField&& other) noexcept;

	~GameField();

	int getWidth() const;

	int getHeight() const;

	bool isCoordsInField(Coords coords_check) const;

	bool isShipCoordsOk(Coords top_left, Ship::Orientation orientation, int size) const;

	void setSize(int width, int height);

	void addShip(Ship& ship, Coords top_left, Ship::Orientation orientation);

	void attack(Coords attack_coords);

	void print_field();
};