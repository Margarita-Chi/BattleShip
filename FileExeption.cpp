#include "FileExeption.h"

FileExeption::FileExeption(std::string message) :
    message(message) {}

std::string FileExeption::what() const noexcept {
    std::string output = "Error with file:" + message + "\n";
    return output;
}
