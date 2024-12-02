#include "ShipManager.h"

ShipManager::ShipManager() = default;

ShipManager::ShipManager(std::vector<int> sizes) {
    for (int size : sizes) {
        Ship* new_ship = new Ship(size);
        ships.emplace_back(new_ship, true);
    }
}

ShipManager::ShipManager(const ShipManager& other) {
    for (const auto& pair : other.ships) {
        Ship* new_ship = new Ship(*pair.first);
        ships.emplace_back(new_ship, pair.second);
    }
}

ShipManager::ShipManager(ShipManager&& other) noexcept
    : ships(std::move(other.ships)) {
    other.ships.clear();
}

ShipManager::~ShipManager() {
    for (auto& pair : ships) {
        delete pair.first;
    }
}

int ShipManager::getDetroyedShipsCount(){
    int count = 0;
    for (const auto& pair : ships) {
        if (pair.first->isDestroyed() && pair.second == false) {
            count++;
        }
    }
    return count;
}

std::vector<Ship*> ShipManager::getAliveShips(){
    std::vector<Ship*> alive_ship;
    for (auto& pair : ships) {
        if (!pair.first->isDestroyed()) {
            alive_ship.push_back(pair.first);
        }
    }
    return alive_ship;
}

int ShipManager::getShipCount() {
    return ships.size();
}

int ShipManager::getFreeShipCount() {
    int count = 0;
    for (const auto& pair : ships) {
        if (pair.second) {
            count++;
        }
    }
    return count;
}

Ship& ShipManager::getShip(int index) {
    if (index >= 0 && index < ships.size()) {
        ships[index].second = false;
        return *(ships[index].first);
    }
}

std::vector<int> ShipManager::getShipSizes(){
    std::vector<int> sizes;
    for (const auto& pair : ships) {
        sizes.push_back(pair.first->getSize());
    }
    return sizes;
}

