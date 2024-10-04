#include "GameField.h"

GameField::GameField()
	: width(0),
	height(0),
	field(nullptr) {}

GameField::GameField(int width, int height)
	: width(width),
	height(height) {
	field = new Cell * [height];
	for (int i = 0; i < height; i++) {
		field[i] = new Cell[width];
	}
}

GameField::GameField(const GameField& other)
	: width(other.width), 
	height(other.height) {
	field = new Cell * [height];
	for (int i = 0; i < height; i++) {
		field[i] = new Cell[width];
		for (int j = 0; j < width; j++) {
			field[i][j] = other.field[i][j];
		}
	}
}

GameField::GameField(GameField&& other) noexcept
	: width(other.width), 
	height(other.height), 
	field(other.field) {
	other.width = 0;
	other.height = 0;
	other.field = nullptr;
}

GameField::~GameField(){
	for (int i = 0; i < height; i++) {
		delete[] field[i];
	}
	delete[] field;
}

int GameField::getWidth() const {
	return width;
}

int GameField::getHeight() const {
	return height;
}

bool GameField::isCoordsInField(Coords coords_check) const {
	if (coords_check.x < 0 || coords_check.x >= width 
		|| coords_check.y < 0 || coords_check.y >= height) {
		return false;
	}
	return true;
}

bool GameField::isShipCoordsOk(Coords top_left, Ship::Orientation orientation, int size) const{
	Coords coords_cell = top_left;
	for (int i = 0; i < size; i++) {
		if (orientation == Ship::Vertical) {
			coords_cell.y = top_left.y + i;
		}
		else {
			coords_cell.x = top_left.x + i;
		}
		if (this->isCoordsInField(coords_cell)) {
			if (field[coords_cell.y][coords_cell.x].ship_is_here || field[coords_cell.y][coords_cell.x].ship_is_nearby) {
				return false;
			}
		} else {
			return false;
		}
	}
	return true;
}


void GameField::setSize(int width, int height){
	if (field) {
		for (int i = 0; i < this->height; i++) {
			delete[] field[i];
		}
		delete[] field;
	}
	this->width = width;
	this->height = height;
	field = new Cell * [height];
	for (int i = 0; i < height; ++i) {
		field[i] = new Cell[width];
	}
}

void GameField::addShip(Ship& ship, Coords top_left, Ship::Orientation orientation) {
	if (!this->isShipCoordsOk(top_left, orientation, ship.getSize())) {
		throw std::out_of_range("Ship coordinates out of range");
		return;
	}
	ship.addToField(orientation, top_left);
	Coords ship_cell = top_left;
	for (int i = 0; i < ship.getSize(); i++) {
		if (ship.getOrientation() == Ship::Vertical) {
			ship_cell.y = top_left.y + i;
		}
		else {
			ship_cell.x = top_left.x + i;
		}
		field[ship_cell.y][ship_cell.x].ship_is_here = true;
		field[ship_cell.y][ship_cell.x].ship_segment_pointer = ship.getSegmentByIndex(i); //тут сегмент
	}

	int add_coord_x;
	int add_coord_y;
	if (orientation == Ship::Vertical) {
		add_coord_x = 1;
		add_coord_y = ship.getSize();
	} else {
		add_coord_x = ship.getSize();
		add_coord_y = 1;
	}

	for (int x = top_left.x - 1; x <= top_left.x + add_coord_x; x++) {
		for (int y = top_left.y - 1; y <= top_left.y + add_coord_y; y++) {
			if (this->isCoordsInField({ x,y })) {
				if (field[y][x].ship_is_here == false) {
					field[y][x].ship_is_nearby = true;
				}
			}
		}
	}
}

void GameField::attack(Coords attack_coords){
	if (!this->isCoordsInField(attack_coords)) {
		return;
	}
	if (field[attack_coords.y][attack_coords.x].ship_is_here) {
		field[attack_coords.y][attack_coords.x].status_cell = Cell::ship;
		field[attack_coords.y][attack_coords.x].ship_segment_pointer->ship_pointer->attackSegment(field[attack_coords.y][attack_coords.x].ship_segment_pointer);
	} else {
		field[attack_coords.y][attack_coords.x].status_cell = Cell::empty;
	}
}

void GameField::print_field(){
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (field[y][x].ship_is_here == true) {
				if (field[y][x].ship_segment_pointer->status == Ship::ShipSegment::damaged) {
					std::cout << "1";
				}
				if (field[y][x].ship_segment_pointer->status == Ship::ShipSegment::destroyed) {
					std::cout << "0";
				} 
				if (field[y][x].ship_segment_pointer->status == Ship::ShipSegment::unharmed) {
					std::cout << "2";
				}
			} else {
				std::cout << "o";
			}
		}
		std::cout << "\n";
	}
}