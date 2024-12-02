#include "Bot.h"
#include <algorithm>
#include <random> 

Bot::Bot(): 
	field(10, 10),
	ship_manager({ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }) {
	shipGenerate(ship_manager);
}

Bot::Bot(std::vector<int> size_ships, int width, int height): 
	field(width, height),
	ship_manager(size_ships) {
	shipGenerate(ship_manager);
}

Bot::Bot(const Bot& other) :
	field(other.field),
	ship_manager(other.ship_manager) {}

Bot::Bot(Bot&& other) noexcept :
	field(std::move(other.field)),
	ship_manager(std::move(other.ship_manager)) {}

Bot::Bot(ShipManager& ship_manager, GameField& field):
	field(field),
	ship_manager(ship_manager){}

void Bot::shipGenerate(ShipManager& ship_manager){
	int ship_manager_size = ship_manager.getShipCount();
	for (int i = 0; i < ship_manager_size; i++) {
		Ship& ship = ship_manager.getShip(i);
		bool flag = true;
		while (flag) {
			try {
				int width = rand() % field.getWidth();
				int height = rand() % field.getHeight();
				Ship::Orientation orientation = static_cast<Ship::Orientation>(rand()%2);
				field.addShip(ship, { width, height }, orientation);
				flag = false;
			} catch (const ShipPlacementExeption& e) {
				flag = true;
			}
		}
	}
}