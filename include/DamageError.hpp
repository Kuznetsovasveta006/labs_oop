#ifndef DAMAGE_ERROR_HPP
#define DAMAGE_ERROR_HPP

#include <string>


class DamageError
{
public:
    explicit DamageError(int damage);
    const std::string what() const noexcept;

private:
    const int damage_error;
};


#endif //  DAMAGE_ERROR_HPP