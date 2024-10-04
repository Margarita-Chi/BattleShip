#include "ship.h"

Ship::Ship() 
	: size(0),
	orientation(Unknown),
	top_left({ -1, -1 }),
	max_health(0),
	health(0) {}

Ship::Ship(int size)
	: size(size),
	orientation(Unknown),
	top_left({ -1, -1 }),
	max_health(size * 2),
	health(size * 2) {}

Ship::Ship(const Ship& other)
	: size(other.size),
	orientation(other.orientation),
	top_left(other.top_left),
	max_health(other.max_health),
	health(other.health),
	segments(other.segments) {}

Ship::Ship(Ship&& other) noexcept
	: size(other.size),
	orientation(other.orientation),
	top_left(other.top_left),
	max_health(other.max_health),
	health(other.health),
	segments(std::move(other.segments)) {}

Ship::~Ship() = default;

int Ship::getSize() const {
	return size;
}

int Ship::getMaxHealth() const {
	return max_health;
}

int Ship::getCurrentHealth() const {
	return health;
}

Ship::Orientation Ship::getOrientation() const{
	return orientation;
}

bool Ship::isUnharmed() {
	return health == max_health;
}

bool Ship::isDestroyed() {
	return health == 0;
}

void Ship::addToField(Ship::Orientation new_orientation, Coords new_top_left){
	orientation = new_orientation;
	top_left = new_top_left;
	Coords current_segment = top_left;
	for (int i = 0; i < size; i++) {
		if (orientation == Horizontal) {
			current_segment.x = top_left.x + i;
		} else {
			current_segment.y = top_left.y + i;
		}
		ShipSegment new_segment;
		new_segment.coords = current_segment;
		new_segment.ship_pointer = this;
		segments.push_back(new_segment);
	}
}

void Ship::attackSegment(ShipSegment* segment){
	if (segment == nullptr) {
		return;
	}
	if (segment->status == ShipSegment::destroyed) {
		return;
	}
	if (segment->status == ShipSegment::damaged) {
		segment->status = ShipSegment::destroyed;
		health--;
	}
	if (segment->status == ShipSegment::unharmed) {
		segment->status = ShipSegment::damaged;
		health--;
	}
}



void Ship::print_info(){
	std::cout << "size " << size << "\n";
	std::cout << "orientation " << orientation << "\n";
	std::cout << "top left [x][y] " << top_left.x << top_left.y << "\n";
	std::cout << "max health " << max_health << "\n";
	std::cout << "health " << health << "\n";
}

Ship::ShipSegment* Ship::getSegmentByIndex(int index){
	if (index < 0 || index >= size) {
		return nullptr;
	}
	return &segments[index];
}