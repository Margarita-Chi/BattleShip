#pragma once

#include <string>

class ShipPlacementExeption{
    std::string message;
public:
    ShipPlacementExeption(std::string message = "");

    std::string what() const noexcept;
};

