#ifndef NO_ABILITY_HPP
#define NO_ABILITY_HPP


#include <string>


class NoAbilityError
{
public:
    explicit NoAbilityError() = default;
    const std::string what() const noexcept;
};


#endif //  NO_ABILITY_HPP