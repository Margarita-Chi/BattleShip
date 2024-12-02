#pragma once

#include <string>

class AttackOutOfFieldExeption{
    std::string message;

public:
    AttackOutOfFieldExeption(std::string message = "");

    std::string what() const noexcept;
};

