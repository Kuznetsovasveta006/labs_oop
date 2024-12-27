#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <fstream>
#include <nlohmann/json.hpp>
#include "FileError.hpp"
class TerminalInput;

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

    void read(TerminalInput& input);

    void closeRead();

    void closeWrite();

    ~FileHandler();
};

#endif // FILE_HANDLER_HPP
