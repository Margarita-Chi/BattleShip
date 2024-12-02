#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include "FileExeption.h"

using json = nlohmann::json;

class FileHandler {
private:
    std::string file_name;
    std::ifstream input_file;
    std::ofstream output_file;
public:
    FileHandler(const std::string& file_name);

    void openForRead();

    void openForWrite();

    void write(const json& info);

    void read(json& info);

    void closeRead();

    void closeWrite();

    ~FileHandler();
};

