#include "FileHandler.h"

FileHandler::FileHandler(const std::string& file_name):
    file_name(file_name){}
 
void FileHandler::openForRead() {
    input_file.open(file_name);
    if (!input_file.is_open()) {
        throw FileExeption("Cann't open file for reading");
    }
}

void FileHandler::openForWrite() {
    output_file.open(file_name);
    if (!output_file.is_open()) {
        throw FileExeption("Cann't open file for writing.");
    }
}

void FileHandler::write(const json& info) {
    if (output_file.is_open()) {
        output_file << info; // .dump(4)
    }
    else {
        throw FileExeption("File don't open for writing.");
    }
}

void FileHandler::read(json& info) {
    if (input_file.is_open()) {
        input_file >> info;
    }
    else {
        throw FileExeption("File don't open for reading.");
    }
}

void FileHandler::closeRead() {
    if (input_file.is_open()) {
        input_file.close();
    }
}

void FileHandler::closeWrite() {
    if (output_file.is_open()) {
        output_file.close();
    }
}

FileHandler::~FileHandler(){
    closeRead();
    closeWrite();
}
