#pragma once

#include<string>

class FileExeption {
    std::string message;

public:
    FileExeption(std::string message = "");

    std::string what() const noexcept;
};