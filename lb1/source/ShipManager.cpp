#include "ShipManager.h"

ShipManager::ShipManager() = default;

ShipManager::ShipManager(std::vector<int> sizes) {
    for (int size : sizes) {
        Ship* new_ship = new Ship(size);
        free_ships.push_back(new_ship);
    }
}

ShipManager::ShipManager(const ShipManager& other){
    for (const Ship* ship : other.free_ships) {
        free_ships.push_back(new Ship(*ship)); 
    }
    for (const Ship* ship : other.active_ships) {
        active_ships.push_back(new Ship(*ship));
    }
}

ShipManager::ShipManager(ShipManager&& other) noexcept 
    : free_ships(std::move(other.free_ships)),
    active_ships(std::move(other.active_ships)) {
    other.free_ships.clear(); 
    other.active_ships.clear();
}

ShipManager::~ShipManager(){
    for (Ship* ship : free_ships) {
        delete ship;
    }
    for (Ship* ship : active_ships) {
        delete ship;
    }
}

int ShipManager::getAliveShipsCount() {
    int count = 0;
    for (Ship* ship : active_ships) {
        if (!ship->isDestroyed()) {
            count++;
        }
    }
    return count;
}

int ShipManager::getDetroyedShipsCount(){
    int count = 0;
    for (Ship* ship : active_ships) {
        if (ship->isDestroyed()) {
            count++;
        }
    }
    return count;
}

int ShipManager::getShipCount() {
    return free_ships.size() + active_ships.size();
}

int ShipManager::getFreeShipCount() {
    return free_ships.size();
}

void ShipManager::addShipToField(GameField& field, int index, Coords new_coord, Ship::Orientation orientation) {
    if (index >= 0 && index < free_ships.size()) {
        Ship* ship_to_add = free_ships[index];
        field.addShip(*ship_to_add, new_coord, orientation);
        active_ships.push_back(ship_to_add);
        free_ships.erase(free_ships.begin() + index);
    }
}