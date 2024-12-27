#ifndef FILE_ERROR_HPP
#define FILE_ERROR_HPP

#include <string>


class FileError
{
public:
    FileError(std::string message = "");
    const std::string what() const noexcept;
    
private:
    const std::string message;
};


#endif // FILE_ERROR_HPP