#include "ShipCollisionError.hpp"


ShipCollisionError::ShipCollisionError(int x, int y)
    : x_error(x), y_error(y)
{}

const std::string ShipCollisionError::what() const noexcept
{
    std::string what = "Cannot place ship at (" + std::to_string(x_error) + ", " + std::to_string(y_error) + "). Space occupied.\n";
    return what;
}