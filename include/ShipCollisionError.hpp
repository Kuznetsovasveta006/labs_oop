#ifndef SHIP_COLLISION_ERROR
#define SHIP_COLLISION_ERROR

#include <string>


class ShipCollisionError
{
public:
    explicit ShipCollisionError(int x, int y);
    const std::string what() const noexcept;

private:
    const int x_error, y_error;
};


#endif //  SHIP_COLLISION_ERROR