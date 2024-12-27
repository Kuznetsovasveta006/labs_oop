#include "FileHandler.hpp"
#include "TerminalInput.hpp"


FileHandler::FileHandler(const std::string& file_name):
    file_name(file_name)
{}
 
void FileHandler::openForRead() {
    input_file.open(file_name);
    if (!input_file.is_open()) {
        throw FileError("Cannot open file for reading.");
    }
}

void FileHandler::openForWrite() {
    output_file.open(file_name);
    if (!output_file.is_open()) {
        throw FileError("Cannot open file for writing.");
    }
}

void FileHandler::write(const json& info) {
    if (output_file.is_open()) {
        output_file << info;
    }
    else {
        throw FileError("File don't open for writing.");
    }
}

void FileHandler::read(json& info) {
    if (input_file.is_open()) {
        input_file >> info;
    }
    else {
        throw FileError("File don't open for reading.");
    }
}

void FileHandler::read(TerminalInput& game_input)
{
    if (input_file.is_open())
    {
        input_file >> game_input;
    }
    else
    {
        throw std::runtime_error("File is not open for reading\n");
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

FileHandler::~FileHandler() {
    closeRead();
    closeWrite();
}