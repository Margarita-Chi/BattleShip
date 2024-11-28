#include "Bot.h"
#include <algorithm>
#include <random> 

Bot::Bot(){
	field = new GameField(10, 10);
	std::vector<int> base_vector = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	ship_manager = new ShipManager(base_vector);
	shipGenerate(ship_manager);
}

Bot::Bot(std::vector<int> size_ships, int width, int height){
	field = new GameField(width, height);
	ship_manager = new ShipManager(size_ships);
	shipGenerate(ship_manager);
}

Bot::Bot(ShipManager* ship_manager, GameField* field):
	field(field),
	ship_manager(ship_manager){}

Bot::~Bot(){
	if (field) {
		delete field;
	}
	if (ship_manager) {
		delete ship_manager;
	}

}

void Bot::shipGenerate(ShipManager* ship_manager){
	int ship_manager_size = ship_manager->getShipCount();
	for (int i = 0; i < ship_manager_size; i++) {
		Ship& ship = ship_manager->getShip(i);
		bool flag = true;
		while (flag) {
			try {
				int width = rand() % field->getWidth();
				int height = rand() % field->getHeight();
				Ship::Orientation orientation = static_cast<Ship::Orientation>(rand()%2);
				field->addShip(ship, { width, height }, orientation);
				flag = false;
			} catch (const ShipPlacementExeption& e) {
				flag = true;
			}
		}
	}
}