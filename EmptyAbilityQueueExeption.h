#pragma once

#include<string>

class EmptyAbilityQueueExeption {
    std::string message;

public:
    EmptyAbilityQueueExeption(std::string message = "");

    std::string what() const noexcept;
};