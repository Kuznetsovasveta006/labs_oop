#include "NoAbilityError.hpp"


const std::string NoAbilityError::what() const noexcept
{
    std::string what = "You have no avaliable abilities. :(";
    return what;
}