#include "Shelling.h"

Shelling::Shelling(ShipManager* ship_manager) :
	ship_manager(ship_manager) {}


void Shelling::applyAbility(){
	std::vector<Ship*> alive_ship = ship_manager->getAliveShips();
	int index = rand() % (alive_ship.size());
	std::vector<int> alive_segments;
	for (int i = 0; i < alive_ship[index]->getSize(); i++) {
		if (alive_ship[index]->getSegmentByIndex(i).getStatus() != Ship::ShipSegment::destroyed) {
			alive_segments.push_back(i);
		}
	}
	int segment_index = rand() % (alive_segments.size());
	alive_ship[index]->getSegmentByIndex(segment_index).attack();
};


