#include "DamageError.hpp"


DamageError::DamageError(int damage)
    : damage_error(damage)
{}

const std::string DamageError::what() const noexcept
{
    std::string what = "Damage value (" + std::to_string(damage_error) + ") is invalid. Damage must be 1 or 2.\n";
    return what;
}