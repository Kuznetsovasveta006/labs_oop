#include "AttackCoordinatesError.hpp"


AttackCoordinatesError::AttackCoordinatesError(int x_error, int y_error)
    : x_error(x_error), y_error(y_error)

{}

const std::string AttackCoordinatesError::what() const noexcept
{
    std::string what = "You cannot attack coordinates: (" + std::to_string(x_error) + ", " + std::to_string(y_error) + ").\n";

    return what;
}