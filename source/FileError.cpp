#include "FileError.hpp"

FileError::FileError(std::string message)
    : message(message) 
{}

const std::string FileError::what() const noexcept 
{
    std::string what = "Error with file:" + message + "\n";
    return what;
}