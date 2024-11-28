#include "Scaner.h"

Scaner::Scaner(Coords coords, GameField* field) :
	coords(coords),
	field(field) {}


void Scaner::applyAbility(){
	for (int x = coords.x; x <= coords.x + 1; x++) {
		for (int y = coords.y; y <= coords.y + 1; y++) {
			if (field->isCoordsInField(coords)) {
				if (field->isShipHere(coords)) {
					std::cout << "You found a ship!\n";
					return;
				}
			}
		}
	}
	std::cout << "You do not found a ship :( \n";
};