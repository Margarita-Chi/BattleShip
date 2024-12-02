#include "EmptyAbilityQueueExeption.h"

EmptyAbilityQueueExeption::EmptyAbilityQueueExeption(std::string message) :
    message(message) {}

std::string EmptyAbilityQueueExeption::what() const noexcept {
    std::string output = "Trying to use ability: " + message + "\n";
    return output;
}
