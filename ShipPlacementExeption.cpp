#include "ShipPlacementExeption.h"

ShipPlacementExeption::ShipPlacementExeption(std::string message) :
    message(message) {}

std::string ShipPlacementExeption::what() const noexcept {
    std::string output = "Trying to add ship to field: " + message + "\n";
    return output;
}