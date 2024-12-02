#include "AttackOutOfFieldExeption.h"

AttackOutOfFieldExeption::AttackOutOfFieldExeption(std::string message) :
    message(message) {}

std::string AttackOutOfFieldExeption::what() const noexcept {
    std::string output = "Trying to attack: " + message + "\n";
    return output;
}