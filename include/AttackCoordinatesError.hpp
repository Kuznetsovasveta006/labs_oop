#ifndef ATTACK_COORDINATES_ERROR_HPP
#define ATTACK_COORDINATES_ERROR_HPP

#include <string>


class AttackCoordinatesError
{
public:
    explicit AttackCoordinatesError(int x_error, int y_error);
    const std::string what() const noexcept;

private:
    const int x_error, y_error;
};


#endif // ATTACK_COORDINATES_ERROR_HPP